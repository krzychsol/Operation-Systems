#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/times.h>
#include <time.h>
#include <unistd.h>

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;
static clock_t prog_st_time;
static struct tms prog_st_cpu;
int tics_per_second;

char buffer[BLOCK_SIZE+1] = "";
int _;

void start_time() {
    st_time = times(&st_cpu);
}

long get_size(FILE* file){
    fseek(file,0,SEEK_END);
    long size = ftell(file);
    fseek(file,0,SEEK_SET);
    return size;
}

char* reverse(char* text){
    size_t n = strlen(text);
    char tmp;

    for(int i=0;i<n/2;i++){
        tmp = text[i];
        text[i] = text[n-i-1];
        text[n-i-1] = tmp;
    }
    return text;
}

int main(int argc,char** argv){
    // Start counting time
    prog_st_time = times(&prog_st_cpu);
    tics_per_second = sysconf(_SC_CLK_TCK);
    if(argc != 3){
        printf("Invalid number of arguments\n");
        return 1;
    }

    char* input_file = argv[1];
    char* output_file = argv[2];
    size_t end;

    FILE* in_file = fopen(input_file,"r");
    FILE* out_file = fopen(output_file,"w");

    long in_file_size = get_size(in_file);
    size_t num_of_blocks = in_file_size / ((size_t) BLOCK_SIZE);
    size_t flag = in_file_size % ((size_t) BLOCK_SIZE);

    for(int i=0;i <= num_of_blocks;i++){
        fseek(in_file,-BLOCK_SIZE*i,SEEK_END);
        end = fread(buffer,sizeof(char),BLOCK_SIZE,in_file);
        buffer[end] = 0;
        fprintf(out_file,"%s",reverse(buffer));
    }

    fseek(in_file,0,SEEK_SET);
    end = fread(buffer,sizeof(char),flag,in_file);
    buffer[end] = 0;
    fprintf(out_file,"%s",reverse(buffer));

    fclose(in_file);
    fclose(out_file);

    en_time = times(&en_cpu);
    printf("======================================================\n");
    printf("Real time: %f s\n", (double) (en_time - prog_st_time) / tics_per_second);
}
