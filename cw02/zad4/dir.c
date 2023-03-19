#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <ftw.h>
#include <errno.h>

long long size_res = 0;

static int display_info(const char* fpath,const struct stat* sb,int tflag){
    if(tflag != FTW_D){
        struct stat bufor_stats;
        stat(fpath,&bufor_stats);
        printf("%s %ld\n",fpath,bufor_stats.st_size);
        size_res += bufor_stats.st_size;
    }
    return 0;
}

int main(int argc, char** argv){
    if( argc != 2){
        printf("Number of arguments is invalid\n");
        return -1;
    }

    char* dir_name = argv[1];
    int err = ftw(dir_name,display_info,1);

    if(err == -1){
        printf("Error during ftw function\n");
        return -2;
    }

    printf("Summary size: %lld",size_res);

    return 0;
}