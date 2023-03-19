/**
 * Zad2 - Wykonane w 100%
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../zad1/library.h"
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

#ifdef DYNAMIC
#include <dlfcn.h>
#endif

#define BUFFER_SIZE 1000

wc_array wc;
short init = 0;
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


int is_str_num(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (!isdigit(str[i])) {
            return 0;
        }
    }
    return 1;
}


void show_help(){
    printf("List of commands:\n");
    printf("init [size] - initialize structure with size [size]\n");
    printf("count [path] - count words in file [path]\n");
    printf("show [index] - show result at index [index]\n");
    printf("delete [index] - delete result at index [index]\n");
    printf("exit - close REPL\n");
    printf("help - show commands\n");
}


int main() {
    // Start counting time
    prog_st_time = times(&prog_st_cpu);

#ifdef DYNAMIC
    void *handle = dlopen("./liblibrary.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Cannot read library file");
        exit(1);
    }

    wc_array (*array_init)(int);
    int (*wc_execute)(char*,struct wc_array *);
    char *(*show_index)(int,struct wc_array *);
    int (*delete_index)(int,struct wc_array *);
    int (*destroy_array)(struct wc_array *);

    array_init = (wc_array (*)(int)) dlsym(handle, "array_init");
    wc_execute = (int (*)(char*,struct wc_array *)) dlsym(handle, "wc_execute");
    show_index = (char *(*)(int,struct wc_array *)) dlsym(handle, "show_index");
    delete_index = (int (*)(int,struct wc_array *)) dlsym(handle, "delete_index");
    destroy_array = (int (*)(struct wc_array *)) dlsym(handle, "destroy_array");
    if (dlerror() != NULL) {
        fprintf(stderr, "Cannot load lib file");
        exit(1);
    }
#endif

    tics_per_second = sysconf(_SC_CLK_TCK);

    char *command = (char *) calloc(BUFFER_SIZE, sizeof(char));

    char delim_for_args[] = "\n\t";
    char delim[] = " \t\r\n\v\f";

    printf("REPL Console\n");
    show_help();
    while (fgets(command, BUFFER_SIZE, stdin) != NULL) {
        start_time();

        char *key = strtok(command, delim);

        //init [size]
        if (!strcmp(key, "init")) {
            if(init){
                printf("Structure is already init\n");
                continue;
            }

            // Get size of array
            key = strtok(NULL, delim);
            if(key == NULL){
                printf("Missing second argument\n");
                continue;
            }

            if(!is_str_num(key)){
                printf("Argument is not a number\n");
                continue;
            }

            int size = (int) strtol(key, NULL, 10);

            wc = array_init(size);

            if(wc.data == NULL && wc.size== 1 && wc.current_size == 0){
                printf("Maximum block size must be greater than 0\n");
                continue;
            }

            if(wc.data == NULL && wc.size == 0 && wc.current_size == 0){
                printf("Failed to initialize structure\n");
                continue;
            }

            init = 1;
            printf("Structure is already allocated with size %d\n", size);
        }

        //count [path]
        else if (!strcmp(key, "count")) {
            if(!init){
                printf("Structure is not init\n");
                continue;
            }

            key = strtok(NULL, delim_for_args);
            if(key == NULL){
                printf("Missing second argument\n");
                continue;
            }

            int index = wc_execute(key,&wc);
            if (index < 0) {
                switch (index) {
                    case -1:
                        printf("You don't have enaugh space in the array\n");
                        break;

                    case -2:
                        printf("Length of file names is longer than 1000 characters\n");
                        break;

                    case -3:
                        printf("Cannot open the file\n");
                        break;

                    case -4:
                        printf("Cannot read the size of tmp.txt\n");
                        break;

                    case -5:
                        printf("Cannot rewind tmp.txt\n");
                        break;

                    default:
                        printf("Error reading tmp.txt\n");
                        break;
                }

                continue;
            }

            printf("Done. Data saved at index %d\n", index);
        }
        //show [index]
        else if (!strcmp(key, "show")) {
            if(!init){
                printf("The array has not been allocated yet\n");
                continue;
            }

            key = strtok(NULL, delim);
            if(key == NULL){
                printf("Missing second argument\n");
                continue;
            }

           if(!is_str_num(key)){
                printf("Argument is not a number\n");
                continue;
            }

            int index = (int) strtol(key, NULL, 10);

            char * result = show_index(index,&wc);
            if (result == NULL) {
                printf("No record at index %d or index is out of range\n", index);
                continue;
            }

            // Print result
            printf("%s\n", result);
        }

        //delete [index]
        else if (!strcmp(key, "delete")) {
            if(!init){
                printf("The array has not been allocated yet\n");
                continue;
            }

            key = strtok(NULL, delim);
            if(key == NULL){
                printf("Missing second argument\n");
                continue;
            }

            if(!is_str_num(key)){
                printf("Argument is not a number\n");
                continue;
            }

            int index = (int) strtol(key, NULL, 10);

            int result = delete_index(index,&wc);

            if (result != 0) {
                switch (result) {
                    case -1:
                        printf("The array has not been allocated yet\n");
                        break;

                    case -2:
                        printf("The index is greater than maximum number of blocks");
                        break;
                    case -3:
                        printf("There is no block under given index");
                        break;
                    default:
                        printf("Unknown error\n");
                        break;
                }

                continue;
            }


            printf("Deleted element at index %d\n", index);
        }

        //destroy array
        else if (!strcmp(key, "destroy")) {
            if(!init){
                printf("The array has not been allocated yet\n");
                continue;
            }

            int result = destroy_array(&wc);
            if (result == 1) {
                printf("No data to destroy\n");
                continue;
            }

            init = 0;
            printf("Structure destroyed\n");
        }
        //exit
        else if (!strcmp(key, "exit")) {
            if(init){
                destroy_array(&wc);
            }
            break;

        }
        //help
        else if (!strcmp(key, "help")) {
            show_help();
        } else {
            printf("Unknown command\n");
        }

        end_time();
    }

    en_time = times(&en_cpu);
    printf("======================================================\n");
    printf("------------- TIME OF WHOLE PROGRAM ---------------\n");
    printf("Real time: %f\t", (double) (en_time - prog_st_time) / tics_per_second);
    printf("User time: %f\t", (double) (en_cpu.tms_utime - prog_st_cpu.tms_utime) / tics_per_second);
    printf("System time: %f\t", (double) (en_cpu.tms_stime - prog_st_cpu.tms_stime) / tics_per_second);

#ifdef DYNAMIC
    dlclose(handle);
#endif

    return 0;
}