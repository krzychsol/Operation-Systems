#include <stdio.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>

int main(){
    clock_t start,end;
    double cpu_time_used;
    start = clock();
    sleep(3);
    end = clock();
    cpu_time_used = (double)(end-start)/CLOCKS_PER_SEC;
    printf("Time: %f\n", cpu_time_used);
    return 0;
}