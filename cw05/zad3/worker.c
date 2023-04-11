#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <fcntl.h>

#define FIFO_PATH "/tmp/integral_queue"
#define BUFF_SIZE 256
char write_buff[BUFF_SIZE] = "";
int _;

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

int main(int argc, char** argv){
    double dx = strtod(argv[1], NULL);
    double a = strtod(argv[2], NULL);
    double b = strtod(argv[3], NULL);

    double result = calculate_integral(a,b,dx);
    size_t size = snprintf(write_buff, BUFF_SIZE, "%lf\n", result);
    int fifo = open(FIFO_PATH, O_WRONLY);
    _ = write(fifo, write_buff, size);
    close(fifo);
    return 0;
}