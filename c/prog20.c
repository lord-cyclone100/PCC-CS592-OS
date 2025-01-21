#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include <sys/wait.h>

int printFibo(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    else{
        return printFibo(n-1) + printFibo(n-2);
    }
}

int main(){

    pid_t pid;
    int num, buffer[2];

    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        
        close(buffer[1]);
        printf("I am child process.\n");
        read(buffer[0],&num,sizeof(int));
        for(int i=0;i<num;i++){
            printf("%d ",printFibo(i));
        }
        close(buffer[0]);
    }

    else{
        close(buffer[0]);
        printf("I am parent process.\n");
        printf("Enter the number of terms : ");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}