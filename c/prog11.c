#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int fibo(int num){
    if(num == 0){
        return 0;
    }
    else if(num == 1){
        return 1;
    }
    else{
        return fibo(num-1)+fibo(num-2);
    }
}

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

    int num1,num2;
    pid_t pid;
    
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        printf("\nEnter a number:");
        scanf("%d",&num1);
        int isPrime = checkPrime(num1);
        if(isPrime == 1){
            printf("%d is prime",num1);
        }
        else{
            printf("%d is not prime",num1);
        }
    }
    else{
        wait(NULL);
        printf("\nEnter a number:");
        scanf("%d",&num2);
        for(int i=0;i<num2;i++){
            printf("%d ",fibo(i));
        }
    }
    return 0;
}