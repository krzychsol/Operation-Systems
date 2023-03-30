#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int fd[2];
    int fd2[2];
    pipe(fd);
    pipe(fd2);
    pid_t pid = fork();
    if (pid == 0){ //child process 
        close(fd[1]);
        char concat_str[100];
        read(fd[0],concat_str, 100);
        int k = strlen(concat_str);
        char* new_message = "Hi dude";
        int i;
        for(i=0;i < strlen(new_message) ;i++){
            concat_str[k++] = new_message[i];
        }
        concat_str[k] = '\0';
        close(fd[0]);
        close(fd2[0]);

        write(fd2[1],concat_str,strlen(concat_str)+1);
        printf(concat_str);
        
        close(fd[1]);
        close(fd2[0]);

    }else if(pid > 0){ //parent process
        close(fd[0]);
        char* message = "Hello world";
        sleep(1);
        write(fd[1], message, strlen(message)+1);
        printf(message);
        close(fd[1]);
        wait(NULL);

    }
    return 0;
}
