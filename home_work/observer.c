
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <proc/readproc.h>

#define CLOCK_TICK sysconf(_SC_CLK_TCK) //number cpu clock tick per second

struct cpustat{
    unsigned long int t_user; // thoi gian o user mode (second)
    unsigned long int t_nice; // thoi gian o nice mode (second)
    unsigned long int t_system; // thoi gian o kernel mode (second)
    unsigned long int t_idle;  // thoi gian o idle mode (second)
    unsigned long int n_ctxt; // so lan doi user va kernel mode 
    unsigned long int t_btime; // thoi diem boot (second)
    unsigned long int n_process; // so process duoc tao 
};

/**
 * In ra thoi gian tinh tu khi boot lan gan nhat
 * Su dung api sysinfo
 * Hoac co the lay thong tin truc tiep tu /proc/uptime
*/
void getTime() {
    struct sysinfo info; 
    int error = sysinfo(&info);
    long timeSecond = info.uptime;
    int time[4];
    time[0] = (int) timeSecond / 86400; timeSecond -= time[0]*86400;
    time[1] = (int) timeSecond / 3600; timeSecond -= time[1]*3600;
    time[2] = (int) timeSecond / 60; timeSecond -= time[2]*60;
    time[3] = (int) timeSecond ;

    printf("Time from lastest boot: ");
    for (int i=0; i<4; i++) {
        if (i < 3)
            printf("%02d:",time[i]);
        else 
            printf("%02d\n\n",time[i]);
    }
}

/**
 * In ra CPU type va model
 * Lay thong tin tu /proc/cpuinfo
 * 
*/
void getCpuInfo() {
    char buf[1024];
    char *val = 0;
    FILE *fp = fopen("/proc/cpuinfo", "r");
    if (!fp)
    {
        perror("opening `/proc/cpuinfo'");
        return ;
    }

    while (fgets(buf, 1024, fp))        /* reads one line */
    {
        char *key = strtok(buf, " ");   /* gets first word separated by space */
        if (!strcmp(key, "model"))
        {
            key = strtok(0, " \t");     /* gets second word, separated by
                                         * space or tab */
            if (!strcmp(key, "name"))
            {
                strtok(0, " \t");         /* read over the colon */
                val = strtok(0, "\r\n");  /* read until end of line */
                break;
            }
        }
    }

    fclose(fp);

    if (val)
    {
        printf("CPU model: ");
        printf("%s \n\n",val);
    }
    else
    {
        fputs("CPU model not found.\n", stderr);
    }
}

/** 
 * Lay thong tin kernel version tu /proc/version
*/
void getKernelVersion() {
    char buf[1024];
    
    FILE* fp = fopen("/proc/version","r");

    if (!fp)
    {
        perror("opening `/proc/version'");
        return ;
    }

    while (fgets(buf, 1024, fp)) {
        char *key = strtok(buf, "(");
        puts(key);
        puts("");
    }
    fclose(fp);
}

unsigned long clockTickToSecond(unsigned long tick) {
    return tick / CLOCK_TICK;
}

void printCpuStat(struct cpustat cpust) {
    printf("Time in user mode: %lu second\nTime in nice mode: %lu second\nTime in system mode: %lu second\n\
Time in idle mode: %lu giay\nTime from latest boot: %lu giay\nSwitch context number: %lu\nNumber processes forked: %lu\n\n", 
            cpust.t_user, cpust.t_nice, cpust.t_system, cpust.t_idle,cpust.t_btime, cpust.n_ctxt, cpust.n_process);
}

/**
 * Folder /proc/stat co cac dong sau
 *  - cpu : co dang | user | nice | system | idle | iowait | irq | softirq | steal | guest | guest_nice |
 *      - user: thoi gian cpu o user mode voi default piority (0)
 *      - nice: niced y chi cac process duoc dieu chinh piority khac 0. Truong nay bieu thi thoi gian cpu chay cac niced process
 *      - system: thoi gian cpu o kernel mode
 *      - idle: thoi gian cpu o che do idle - khong thuc hien cau lenh hay cho doi I/O
 *      - iowait: thoi gian cpu cho I/O
 *      - irq: thoi gian cpu phuc vu ngat cung
 *      - softirq: thoi gian cpu phuc vu ngat mem
 *      - steal: thoi gian cpu phuc vu cac OS khac khi chay ao hoa
 *      - guest: thoi gian chay cac process tren cpu ao hoa voi default piority
 *      - guset_nice: thoi gian chay cac process tren cpu ao hoa voi default piority
 *  - cpu0: thoi gian chay cua cpu thu 0, cac truc tuong tu nhu dong tren.
 *  intr: so ngat duoc phuc vu. So dau tien la tong so ngat, cac so tiep theo chi so luong cac loai ngat khac nhau.
 *  ctxt: chi so lan chuyen doi giua user mode va cpu mode 
 *  btime: thoi diem OS duoc boot, tinh theo giay bat dau tu Unix POSIX
 *  processes: so luong process va thread duoc tao ra.
 *  procs_running: so luong cac process dang chay 
 *  procs_blocked: so luong cac process dang bi block doi I/O
 *  softirq: so dau tien chi tong cac ngat mem, cac so sau chi so luong ngat mem moi loai
*/

void getCpuStat(struct cpustat* cpust) {
    char buf[1024];
    char *val = 0;
    FILE *fp = fopen("/proc/stat", "r");
    if (!fp)
    {
        perror("opening `/proc/stat'");
        return ;
    }
    int c = 0;
    while (fgets(buf, 1024, fp)) {
        char fieldName[32];
        sscanf(buf,"%s",fieldName);
        if (strcmp(fieldName,"cpu") == 0) {
            sscanf(buf,"%s  %lu %lu %lu %lu", fieldName, &(cpust->t_user), &(cpust->t_nice), &(cpust->t_system), &(cpust->t_idle));
            cpust->t_user = clockTickToSecond(cpust->t_user);
            cpust->t_nice = clockTickToSecond(cpust->t_nice);
            cpust->t_system = clockTickToSecond(cpust->t_system);
            cpust->t_idle = clockTickToSecond(cpust->t_idle);
        } else if (strcmp(fieldName,"ctxt") == 0) {
            sscanf(buf,"%s %lu", fieldName, &(cpust->n_ctxt));
        } else if (strcmp(fieldName,"btime") == 0) {
            sscanf(buf,"%s %lu", fieldName, &(cpust->t_btime));
        } else if (strcmp(fieldName,"processes") == 0) {
            sscanf(buf,"%s %lu", fieldName, &(cpust->n_process));
        } else {

        }
    }
    printCpuStat(*cpust);
    fclose(fp);
}

/**
 * Get sample load 
 * Y tuong se la: doc het cac directory co dang /proc/'*'/status voi * la pid cua cac process hien tai
 * Lay tong so cac process co state la: R(running) va D(disk waiting)
 * Ta se dung api readproc()
*/
int sampleLoadAverage() {
    int load = 0;

    PROCTAB* proc = openproc(PROC_FILLSTATUS); // doc file status cua cac process

    proc_t proc_info;
    memset(&proc_info, 0, sizeof(proc_info));

    while (readproc(proc, &proc_info) != NULL) {
        if (proc_info.state == 'D' || proc_info.state == 'R') {
            load += 1;
        }
    }
    closeproc(proc);

    return load;
}

/**
 * Get load average
 * De co ket qua chinh xac hon, ta co the tinh thoi gian chay t_run cua ham lay mau 
 * Luc do: t_sleep = t_sample - t_run
*/
void getLoadAverage(int interval, int duration) {
    int iteration=0;
    int totalLoad = 0;
    int timeSampled = duration / interval;

    while (iteration < duration) {
        sleep(interval);
        totalLoad += sampleLoadAverage();
        iteration = iteration + interval;
    }

    float loadAvg = totalLoad / timeSampled;
    printf("Tai trung binh cua he thong trong thoi gian %d, chu ki lay mau %d, la: %f\n\n", duration, interval, loadAvg);
}

/**
 * Lay thong tin ve RAM tu /proc/meminfo
*/
void getMemInfo() {
    char buf[1024];
    char *val = 0;
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp)
    {
        perror("opening `/proc/meminfo'");
        return ;
    }

    while (fgets(buf, 1024, fp))        /* reads one line */
    {
        char *key = strtok(buf, " \t");   /* gets first word separated by space or tab */
        if (strcmp(key, "MemTotal:") == 0)
        {
            val = strtok(0, "\r\n");  /* read until end of line */
            printf("Tong so RAM duoc cap: %s\n", val);
        } else if (strcmp(key, "MemAvailable:") == 0) {
            val = strtok(0, "\r\n");  /* read until end of line */
            printf("Tong so RAM kha dung: %s\n\n", val);
        }
    }


    fclose(fp);
}

int main(int argc, char **argv)
{
    struct cpustat cpust;
    getTime();
    getCpuInfo();
    getKernelVersion();
    getCpuStat(&cpust);
    getMemInfo();
    if (argv != NULL) {
        if (argc == 4 &&  strcmp(argv[1],"-s") == 0) {
            int interval = atoi(argv[2]);
            int duration = atoi(argv[3]);
            getLoadAverage(interval, duration);
        } else {
            printf("Incorrect argument!");
            exit(0);
        }
    } 
    return 0;
}