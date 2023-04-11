#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>

double f(double x) {
    return 4.0 / (x*x + 1);
}

double calculate_integral(double a, double b, double dx) {
    double sum = 0;
    double x = a;
    while (x < b) {
        sum += f(x) * dx;
        x += dx;
    }
    return sum;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Invalid number of arguments");
        return -1;
    }

    double dx = atof(argv[1]);
    int num_procs = atoi(argv[2]);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    int fd[num_procs][2];
    double result[num_procs];

    for (int i = 0; i < num_procs; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            return -1;
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return -1;
        } else if (pid == 0) {
            // child process
            double a = (double)i / num_procs;
            double b = (double)(i+1) / num_procs;
            result[i] = calculate_integral(a, b, dx);
            close(fd[i][0]);
            write(fd[i][1], &result[i], sizeof(result[i]));
            close(fd[i][1]);
            exit(0);
        }
    }

    double total_sum = 0;
    for (int i = 0; i < num_procs; i++) {
        close(fd[i][1]);
        double proc_sum;
        read(fd[i][0], &proc_sum, sizeof(proc_sum));
        close(fd[i][0]);
        total_sum += proc_sum;
        wait(NULL);
    }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("dx=%f num_procs=%d result=%f elapsed_time=%f\n", dx, num_procs, total_sum, elapsed_time);
    return 0;
}
