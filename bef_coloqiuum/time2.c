#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

static clock_t st_time;
static clock_t en_time;
static clock_t prog_st_time;

static struct tms st_cpu;
static struct tms en_cpu;
static struct tms prog_st_cpu;

int tics_per_sec;

void start_time(){
    st_time = times(&st_cpu);
}

void end_time(){
    en_time = times(&en_cpu);
    printf("Real time: %f\n", (double)(en_time-st_time)/tics_per_sec);
    printf("User time: %f\n", (double)(en_cpu.tms_utime-st_cpu.tms_utime)/tics_per_sec);
    printf("System time: %f\n", (double)(en_cpu.tms_stime-en_cpu.tms_stime)/tics_per_sec);
}

int main(){
    tics_per_sec = sysconf(_SC_CLK_TCK);
    start_time();
    sleep(2);
    end_time();
    
    return 0;
}