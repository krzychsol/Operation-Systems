#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/times.h>
#include <sys/stat.h>
#include <time.h>

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;
static clock_t prog_st_time;
static struct tms prog_st_cpu;
int tics_per_second;

size_t _;

typedef struct{
    FILE* lib;
    int sys;
} File;

void start_time() {
    st_time = times(&st_cpu);
}

size_t get_size(File file){
#ifndef SYS
    fseek(file.lib,0,SEEK_END);
    long size = ftell(file.lib);
    fseek(file.lib,0,SEEK_SET);
    return size;
#else
    struct stat st;
    fstat(file.sys, &st);
    return st.st_size;
#endif
};

File open_file(char* path,char MODE){
    File file;
#ifndef SYS
    file.lib = fopen(path,MODE == 'r'? "r":"w");    
#else
    file.sys = open(path,MODE == 'r'? O_RDONLY: O_WRONLY); 
#endif
    return file;
}

char* read_file(char* filepath){
    File file = open_file(filepath,'r');
    size_t size = get_size(file);
    char* buffer = (char*)calloc(size,sizeof(char));

#ifndef SYS
    _ = fread(buffer,sizeof(char),size,file.lib);
    fclose(file.lib);
#else
    _ = read(file.sys,buffer,sizeof(char)*size);
    close(file.sys);
#endif
    return buffer;
}

void write_file(char* filepath,char* buffer){
    File file = open_file(filepath,'w');

#ifndef SYS
    _ = fwrite(buffer,sizeof(char),strlen(buffer),file.lib);
    fclose(file.lib);
#else
    _ = write(file.sys,buffer,strlen(buffer)*sizeof(char));
    close(file.sys);
#endif
    
}

int main(int argc,char** argv){
    // Start counting time
    prog_st_time = times(&prog_st_cpu);
    tics_per_second = sysconf(_SC_CLK_TCK);
    
    if(argc != 5){
        printf("invalid number of algruments passed\n");
        return 1;
    }
       
    char start_char = argv[1][0];
    char target_char = argv[2][0];
    char* input_filename = argv[3];
    char* output_filename = argv[4];

    char* file_content = read_file(input_filename);

    char* tmp = file_content;
    while (*tmp){
        if(*tmp == start_char){
            *tmp = target_char;
        }
        tmp++;
    }    

    write_file(output_filename,file_content);

    en_time = times(&en_cpu);
    printf("======================================================\n");
    printf("Real time: %f s\n", (double) (en_time - prog_st_time) / tics_per_second);

    return 0;
}