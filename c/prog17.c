#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){

    pid_t pid;
    pid = fork();
    
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        printf("Child process\nCurrent process : %d\tParent process : %d\n",getpid(),getppid());
    }
    else{
        printf("Parent process\nCurrent process : %d\tChild process : %d\n",getpid(),pid);
    }

    return 0;
}