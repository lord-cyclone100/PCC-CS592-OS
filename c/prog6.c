#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int checkPrime(int num){
    if(num <= 1){
        return 0;
    }
    for(int i=num-1;i>1;i--){
        if(num%i == 0){
            return 0;
        }
        else{
            return 1;
        }
    }
}

int main(){

    int buffer[2], num;
    pid_t pid;

    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&num,sizeof(int));
        int isPrime = checkPrime(num);
        if(isPrime == 1){
            printf("%d is prime",num);
        }
        else{
            printf("%d is not prime",num);
        }
        close(buffer[0]);
    }

    else{
        close(buffer[0]);
        printf("Enter a number:");
        scanf("%d",&num);
        write(buffer[1],&num,sizeof(int));
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}