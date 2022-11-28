#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/resource.h>

const char content[] = "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";
const size_t contentLen  = sizeof(content)/sizeof(content[0]) ;
char fileName[] = "test.txt";
const char resultFile1[] = "result1.txt";
const char resultFile2[] = "result2.txt";

typedef struct
{
  bool done;
  pthread_mutex_t mutex;
  char message[2048];
} shared_data;

static shared_data* data = NULL;

void initialise_shared()
{
    // place our shared data in shared memory
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_SHARED | MAP_ANONYMOUS;
    data = mmap(NULL, sizeof(shared_data), prot, flags, -1, 0);
    assert(data);

    data->done = false;

    // initialise mutex so it works properly in shared memory
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&data->mutex, &attr);
}

void run_child()
{
    struct timespec wStart, wStop;
    struct rusage usage;
    pthread_mutex_lock(&data->mutex);

	// child process will write to shared process
	clock_gettime(CLOCK_MONOTONIC, &wStart);
	memcpy(data->message,content,contentLen);
    data->done = true;
	clock_gettime(CLOCK_MONOTONIC, &wStop);

    getrusage(RUSAGE_SELF,&usage);

	FILE* result = fopen(resultFile1,"a+");

    fprintf(result,"(1w %ld %ld)\n", wStart.tv_sec, wStart.tv_nsec);
    fprintf(result,"(2w %ld %ld)\n", wStop.tv_sec, wStop.tv_nsec);
    fprintf(result,"(3w %ld)\n", usage.ru_maxrss);

    pthread_mutex_unlock(&data->mutex);

}

// parent process will read from shared memory 
void run_parent(pid_t pid)
{
    struct timespec rStart, rStop;
    struct rusage usage;
	char buf[contentLen];

	while (true)
	{
		pthread_mutex_lock(&data->mutex);
		if (data->done) {
			clock_gettime(CLOCK_MONOTONIC, &rStart);
			memcpy(buf, data->message, contentLen);
			clock_gettime(CLOCK_MONOTONIC, &rStop);

            getrusage(RUSAGE_SELF,&usage);

            if (strcmp(buf, content) == 0) {
                // ghi ket qua
                FILE* result = fopen(resultFile1,"a+");
                fprintf(result,"(1r %ld %ld)\n", rStart.tv_sec, rStart.tv_nsec);
                fprintf(result,"(2r %ld %ld)\n", rStop.tv_sec, rStop.tv_nsec);
                fprintf(result,"(3r %ld)\n", usage.ru_maxrss);
                fclose(result);
            } else {
                FILE* result = fopen(resultFile1,"a+");
                fprintf(result,"doc sai \n");
                fclose(result);
            }

			pthread_mutex_unlock(&data->mutex);
			break;
		}
		pthread_mutex_unlock(&data->mutex);
	}

    // waitpid(pid, NULL, WNOHANG);
}

int main(int argc, char** argv)
{
    initialise_shared();

    pid_t pid = fork();
    if (!pid) {
        run_child();
    }
    else {
        run_parent(pid);
    }

    munmap(data, sizeof(data));
    return 0;
}
