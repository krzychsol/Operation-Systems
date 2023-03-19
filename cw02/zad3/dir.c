#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char** argv){
    if( argc != 2){
        printf("Number of arguments is invalid\n");
        return -1;
    }

    char* dir_name = argv[1];
    DIR* dir = opendir(dir_name);

    if( dir == NULL ){
        printf("Can't read this directory");
        return -2;
    }

    struct dirent* cur_file;
    long long size_res = 0;
    struct stat bufor_stats;

    while((cur_file = readdir(dir))){
        stat(cur_file->d_name,&bufor_stats);

        if(!S_ISDIR(bufor_stats.st_mode)){
            printf("%s %ld\n",cur_file->d_name,bufor_stats.st_size);
            size_res += bufor_stats.st_size;
        }
    }

    int close_res = closedir(dir);
    if(close_res == -1){
        printf("Failed to close this directory\n");
        return -3;
    }
    
    printf("Summary files size: %lld\n",size_res);
    return 0;
}