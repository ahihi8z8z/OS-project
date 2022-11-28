#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include<unistd.h>

const char content[] = "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";
const size_t contentLen  = sizeof(content)/sizeof(content[0]) ;
char fileName[] = "test.txt";
const char resultFile[] = "time_message_queue.txt";

struct my_msgbuf {
    long mtype;
    char mtext[2048];
};

/*child process will send message*/
void run_child(int msqid) {

    struct my_msgbuf buf;

    buf.mtype = 1; // loai message.
    memcpy(buf.mtext, content,contentLen);

    struct timespec wStart, wStop;
    clock_gettime(CLOCK_MONOTONIC, &wStart);
    msgsnd(msqid, &buf, contentLen, 0); /*Gui message di*/
    clock_gettime(CLOCK_MONOTONIC, &wStop);

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
       perror("msgctl");
       exit(1);
    }

    FILE* result = fopen(resultFile,"a+");
    fprintf(result,"(1w %ld %ld)\n", wStart.tv_sec, wStart.tv_nsec);
    fprintf(result,"(2w %ld %ld)\n", wStop.tv_sec, wStop.tv_nsec);
    fclose(result);
}

/*parent process will read message from queue*/
void run_parent(key_t key) {
    struct my_msgbuf buf;
    int msqid;
   
    if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }

    struct timespec rStart, rStop;

    clock_gettime(CLOCK_MONOTONIC, &rStart);
    for(;;) { /* parent process se lien tuc doc message tu queue*/
        msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0); 

        if (strcmp(buf.mtext,content) == 0)
            break;
    }
    clock_gettime(CLOCK_MONOTONIC, &rStop);

    if (strcmp(buf.mtext, content) == 0) {
        // ghi ket qua
        FILE* result = fopen(resultFile,"a+");
        fprintf(result,"(1r %ld %ld)\n", rStart.tv_sec, rStart.tv_nsec);
        fprintf(result,"(2r %ld %ld)\n", rStop.tv_sec, rStop.tv_nsec);
        fclose(result);
    } else {
        FILE* result = fopen(resultFile,"a+");
        fprintf(result,"doc sai \n");
        fclose(result);
    }
}
int main() {
    int msqid;
    key_t key;

    system("touch msgq.txt");
    /*ftok se tao 1 id xac dinh luu trong msgq.txt*/
    if ((key = ftok("msgq.txt", 'B')) == -1) {
       perror("ftok");
       exit(1);
    }

    /*tao 1 message queue ung voi key*/
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    pid_t writeProcess;

    writeProcess = fork();
    
    if (writeProcess == 0) {
        run_child(msqid);
    } else {
        run_parent(key);
    }
    return 0;
}