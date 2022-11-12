#include <fcntl.h> // thu vien dinh nghia khoa file
#include <stdio.h> // thu vien vao ra co ban
#include <unistd.h> // thu vien cac API POSIX co ban

/**
 * Khoa file co 2 loai la khoa doc (F_RDLCK) va khoa ghi (F_WRLCK):
 *      - Khoa doc co the duoc giu boi nhieu process, khi file bi 
 *        gan khoa doc thi cac process khong the ghi vao file.
 *      - Khoa ghi chi co the duoc giu boi 1 process, khi file bi 
 *        gan khoa ghi thi khong co process nao co the doc hay ghi vao file
 * 
 * Child process se thua huong khoa file ma process cha dang giu.
*/

int main(int argc, int** argv) {
    struct flock fl; // struct cua 1 khoa file 
    int fd; // file descriptor
    int type = O_RDONLY;

    //set up cac truong cho khoa file
    fl.l_pid = getpid(); // process hien tai cam khoa file
    fl.l_type = F_WRLCK; // khoa ghi
    fl.l_whence = SEEK_SET ; // lay moc tu vi tri dau tien cua file
    fl.l_start = 0; // khoa bat dau tai moc l_whence
    fl.l_len = 0; // khoa den ghi gap EOF

    fd = open("locked_file.txt",type); // mo file voi quyen cho truoc

    if( fd == -1) {
        if (type == O_RDONLY)
            printf("Khong the mo file voi quyen doc!");
        else 
            printf("Khong the mo file voi quyen ghi!");
    } else {
        if (type == O_RDONLY)
            printf("Da mo file voi quyen doc!");
        else 
            printf("Da mo file voi quyen ghi!");        
    }

    fcntl(fd, F_SETLKW, &fl); // gan khoa vao file. Voi F_SETLTW, neu file dang bi khoa, process se doi den khi file duoc mo khoa.

    sleep(120); // 
}