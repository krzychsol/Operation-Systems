// MIERZENIE CZASU
#include <sys/times.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;
static clock_t prog_st_time;
static struct tms prog_st_cpu;
int tics_per_second;


void start_time() {
    st_time = times(&st_cpu);
}


void end_time() {
    en_time = times(&en_cpu);
    printf("------------------ TIME ---------------------\n");
    printf("Real time: %f\t", (double) (en_time - st_time) / tics_per_second);
    printf("User time: %f\t", (double) (en_cpu.tms_utime - st_cpu.tms_utime) / tics_per_second);
    printf("System time: %f\t\n", (double) (en_cpu.tms_stime - st_cpu.tms_stime) / tics_per_second);
}

int main(){
    // Start counting time
    prog_st_time = times(&prog_st_cpu);
    tics_per_second = sysconf(_SC_CLK_TCK);

    long int sum = 0;
    for(int i=0;i<1000000;i++){
        sum += i;
    }
    sleep(2);
    printf("Sum: %ld \n", sum);

    en_time = times(&en_cpu);
    printf("======================================================\n");
    printf("------------- TIME OF WHOLE PROGRAM ---------------\n");
    printf("Real time: %f\t", (double) (en_time - prog_st_time) / tics_per_second);
    printf("User time: %f\t", (double) (en_cpu.tms_utime - prog_st_cpu.tms_utime) / tics_per_second);
    printf("System time: %f\t", (double) (en_cpu.tms_stime - prog_st_cpu.tms_stime) / tics_per_second);
    return 0;
}
