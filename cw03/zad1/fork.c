#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char* argv[]){
    
    char *p;
    int child_ps_num = strtol(argv[1],&p,10);
    int status = 0;

    for(int i=0;i<child_ps_num;i++){
        pid_t pid = fork();

        if(pid == 0){
            printf("%d | ",i);
            printf("Parent Process ID: %d, Process ID: %d\n", getppid(), getpid());
            exit(0);
        }
    }

    while(wait(NULL) > 0);
    printf("argv[1] = %d\n", child_ps_num);

    return 0;
}