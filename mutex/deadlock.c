#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define MAX_THREAD 1

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

pthread_t tid[MAX_THREAD];
int counter = 0;

void *threadFunc(void *argv)
{
	pthread_mutex_lock(&mutex1);
	counter += 1;
	printf("Thread has started, counter %d\n", counter);
	usleep(10);
    pthread_mutex_lock(&mutex1);
    counter += 1;
    usleep(10);
    pthread_mutex_unlock(&mutex1);
	printf("Thread has finished, counter %d\n", counter);
	pthread_mutex_unlock(&mutex1);

	pthread_exit(NULL);
}
int main() {
    int i = 0;
	int ret = 0;

	for (i = 0; i < MAX_THREAD; i++)
	{
		ret = pthread_create(&(tid[i]), NULL, threadFunc, NULL);
		if (ret != 0)
		{
			printf("Thread [%d] created error\n", i);
		}
	}

	pthread_join(tid[0], NULL);
}