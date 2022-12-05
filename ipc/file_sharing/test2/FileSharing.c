#include <fcntl.h> // thu vien dinh nghia khoa file
#include <stdio.h> // thu vien vao ra co ban
#include <unistd.h> // thu vien cac API POSIX co ban
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>

/**
 * Khoa file co 2 loai la khoa doc (F_RDLCK) va khoa ghi (F_WRLCK):
 *      - Khoa doc co the duoc giu boi nhieu process, khi file bi 
 *        gan khoa doc thi cac process khong the ghi vao file.
 *      - Khoa ghi chi co the duoc giu boi 1 process, khi file bi 
 *        gan khoa ghi thi khong co process nao co the doc hay ghi vao file
 * 
 * Child process se thua huong khoa file ma process cha dang giu.
*/
// const char content[] = "1a7rN99lFPZwnPzH47H7uow5irH0moY3akriTiVCCkkDMT7lLa6AGK5X8iOHxkUerGAYQiEY3dPiwafQKKsSRgydthjUbSJTak3WmMmkXm8NfuGOhH0eBSCrpHDeZbUsdb6O9rZZo0eJXeyCP7URA776nyYhmb644vdR6cbFAARjNIBBzp0fDjFDJms4aSooE945sFEXqn1tn6ztJUnvmQIY85AbUNZdyajQhazgJVcsfuVH331sH5FJrE05QrUCd8E5n1aH1nnz4y9LhjSYfdSDVGxkrUWtZ1mOIDBdGL0o1mZdveyFxcJunTEKyYKf04jv8XNemTx5oFC6D5s0Yv9nyzrtNnIlwwOulXZZQCMymNDnw8WQvl8C2ZsYDHYF7ySdw3KNaRlurL4lKWzPBNQ4FohVNli6y3oOhrc59maba9qcPt7DqxQRBzuCDJo0cwSefpeUQTG0DGJYtCMqDnVpVeCAycEqr1zdyUSAQtjT8Wboy0dG2l3slDAQZbUwaky4yh9eSffjlsFtZX2dd9rj9eEZtkh6Ets5hHHwp3ZngUnAcGQXoh8EXNuNOSbDLmoj3H8FSCHKU4bcxKujCBcrBGA69ms1Forj0YNjUhQJhXmFc3A78zbb9indyV8mTnn47fUsbnf5hc4p72pAX1bxBrZBMLrN0ZDT7HgKB1Ntj5PXUVtUXvf4GLApxB68iCF8bX0OcqKud4lBBryFIsVZ584p8ra2dW23qRx0ChmKFPXPqd2aHc4ZMWCaf114wqXGmjGymalKV6OzvmzNogGB0H9iE89GbyJ5vSvfbE3Dbr0GX2KR2LaN2ijEEJfXXhjq7fI4kpcqjVzmboOo8aE56xj6FV4UwIPr7GQkm9P0O6RqxzQyhP1LWn7Fdw9s7JdIwrc4Fmpy5HeqKpH1exBDHDnAXDZdJhppW89Ksdr8p1HpkEV4SqqXJrmTKXs8wlwm0ShM3LhCxGjqXZuwfRcFGAaLz8XDTyhuG6TC1bojUh0v9HNyqyrttu01hF1cAMScJ8dL1Aqh96OZou7WX86dF1LdaK57oH423Ug9sXgd56SiUB3aNEjjjpl0qvl2sfj2mF38uQzZLZUGaNHY7hTD67RQ3Lv1HwtEAqTUGtoYeAGv4DwTORcjasDzPB0AVLL49zrlGjAIRe7v6eYqi8PubwjrWP21JgwMls3RS8df7Smrfdrjw51rVwiZmUynX1QuQFggnHzlOeOLssLDBMHD6P7csKaxdvubbvQCAr4DTw6Wcm5BrgbG7IjpqRvBbfUzpblIrvVrqGFqqQoaqjFG8CHUIjVkWBqU3p124FJCZTCxVlFAI2L8t7Cz4GZ6Q0TGFx7JUp0K7UXf76B0AQhWxJxosmeGA5yFUPQyhfbw3cdIEawxEAQldsfQ1Sa54quIuvDIzjnnUBYXv2bjKnwQLumXDGFaryo4WacXk7tznF9xP6YgAkBh2JyDekz9BN0qFVsGDxQgMKaSyAI3EEeKq4Tw5EIlQcIWsSbUb56EAKiSeCDERl3FkUrQDXb37TNSkBa1Vw4rOCpwLNRxs3JnUEptguOujE8JcSMkR2tFg0uZZ4Fa2HUydznk4Y23RFEnjeiwT3AngeqCt5u3WqOY7euy2aANSCaR6BJ4icLUwPqb38PIjryhFmjz6S1jzu5rRI8lgMukFQBylttvlViQsiwERTPg6pqfeRIfZFzfAjmgtiq6kUd7Vfui6aLyPzKh5ZtUyOzc07f6bzAfRkCb1G2I9PJDaT1qcEauhWb7mGwF3vpBMOfv3mtUU6ws9qGuj3wAW4i7IJxlsC2tk4LVX1JpKB4MiosPAbpWxhr3rstQNQYrkNZDuKXujK2AfB15Fida2TtJyMtoBuod0DfQwDKYrtjWyWVBbzNPsdkHyCL4Kye1o2QqRU7ZPmrYiGWiG3A98DbQGTZijQ2wb6SjysDkUekMPLAZA4dBNifMjxF7opU2D3mj1vQfUKdgSII31EKAQ74eM2JgEOQIyAhhlR6GKZkl0KI9buqGrPrS7m9CMpZNMoJRlPtzU0n";
const char content[] = "hai";
const size_t contentLen  = sizeof(content)/sizeof(content[0]) ;
char fileName[] = "test.txt";
const char resultFile1[] = "result1.txt";
const char resultFile2[] = "result2.txt";

// read content from file to buf n time 
void readStringToFile(const char* fileName, char* buf, long time) {
    int fd;
    
    for (long i = 0; i <  time ; i++) {
        do {
            fd = open(fileName,O_RDONLY); // mo file voi quyen cho truoc
            read(fd,buf,contentLen);
            // printf("%s","run ");
        } while (strcmp(buf, content) != 0);

        lseek(fd,contentLen, SEEK_CUR); // doc xong thi dich chuyen con tro file den string moi
    }
    close(fd);
}

// ghi vao file time lan
void writeStringToFile (const char* fileName, struct flock* fl, long time) {
    int fd; // file descriptor
    fd = open(fileName,O_WRONLY | O_CREAT,S_IRWXU); // mo file voi quyen cho truoc
    for (long i = 0; i < time; i++) {
        fcntl(fd, F_SETLKW, fl); // gan khoa vao file. Voi F_SETLTW, neu file dang bi khoa, process se doi den khi file duoc mo khoa.
        write(fd,content,contentLen);
        fl->l_type   = F_UNLCK;
        fcntl(fd, F_SETLK, &fl); /* unset lock */
    }

    close(fd);
}

void run_parent1(char *argv[]) {
    struct timespec rStart, rStop;
    struct rusage usage;
    char* buf = (char*) malloc(contentLen);// buffer dung cho read
    long count = strtol(argv[1],NULL,10);
    // thuc hien doc file trong process con
    clock_gettime(CLOCK_MONOTONIC, &rStart);

    readStringToFile(fileName,buf,count);

    clock_gettime(CLOCK_MONOTONIC, &rStop);

    getrusage(RUSAGE_SELF,&usage);
    // ghi ket qua
    FILE* result = fopen(resultFile2,"a+");
    fprintf(result,"(1r %ld %ld)\n", rStart.tv_sec, rStart.tv_nsec);
    fprintf(result,"(2r %ld %ld)\n", rStop.tv_sec, rStop.tv_nsec);
    fprintf(result,"(3r %ld)\n", usage.ru_maxrss);
    fclose(result);

    free(buf);
}

void run_child1(char *argv[]) {
    struct timespec wStart, wStop;
    struct rusage usage;
    struct flock fl; // struct cua 1 khoa file 
    //set up cac truong cho khoa file
    fl.l_pid = getpid(); // process hien tai cam khoa file
    fl.l_type = F_WRLCK; // khoa ghi
    fl.l_whence = SEEK_SET ; // lay moc tu vi tri dau tien cua file
    fl.l_start = 0; // khoa bat dau tai moc l_whence
    fl.l_len = 0; // khoa den ghi gap EOF

    long count = strtol(argv[1],NULL,10);
    // thuc hien ghi vao file trong process cha
    clock_gettime(CLOCK_MONOTONIC, &wStart);
    writeStringToFile(fileName,&fl,count);
    clock_gettime(CLOCK_MONOTONIC, &wStop);
    getrusage(RUSAGE_SELF,&usage);
    
    // ghi lai ket qua
    FILE* result = fopen(resultFile2,"a+");
    fprintf(result,"(1w %ld %ld)\n", wStart.tv_sec, wStart.tv_nsec);
    fprintf(result,"(2w %ld %ld)\n", wStop.tv_sec, wStop.tv_nsec);
    fprintf(result,"(3w %ld)\n", usage.ru_maxrss);
    fclose(result);
}

int main(int argc, char *argv[]) {
    pid_t writeProcess;
    
    writeProcess = fork(); // tao process con 

    if (writeProcess == 0) {
        /*Ghi vao file trong child process*/
        run_child1(argv);

    } else if (writeProcess > 0){
        /*Doc tu file trong parent process*/
        run_parent1(argv);
    } else {
        return -1;
    }
    return 0;
}
