#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_PATH "/tmp/integral_queue"
#define BUFF_SIZE 2048
char write_buff[BUFF_SIZE] = "";
char read_buff[BUFF_SIZE] = "";
int _;

char arg2[BUFF_SIZE];
char arg3[BUFF_SIZE];

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Invalid number of arguments");
        return -1;
    }

    double dx = atof(argv[1]);
    int num_programms = atoi(argv[2]);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    mkfifo(FIFO_PATH, 0666);

    for (int i = 0; i < num_programms; i++) {
        if (!fork()) {
            double a = (double)i / num_programms;
            double b = (double)(i+1) / num_programms;
            snprintf(arg2, BUFF_SIZE, "%lf", a);
            snprintf(arg3, BUFF_SIZE, "%lf", b);
            execl("./worker", "worker", argv[1], arg2, arg3, NULL);
        }
    }

    double total_sum = 0.0;
    int fifo = open(FIFO_PATH, O_RDONLY);
    int read_cnt = 0;

    while (read_cnt < num_programms){
        size_t size = read(fifo, read_buff, BUFF_SIZE);
        read_buff[size] = 0;

        char delim[] = "\n";
        char* token;

        token = strtok(read_buff, delim);
        for (;token; token = strtok(NULL, delim)){
            total_sum += strtod(token, NULL);
            read_cnt++;
        }
    }
    close(fifo);
    remove(FIFO_PATH);

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("dx=%f num_of_programms=%d result=%f elapsed_time=%f\n", dx, num_programms, total_sum, elapsed_time);
    return 0;
}
