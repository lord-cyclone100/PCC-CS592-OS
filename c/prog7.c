#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h>

void checkArmstrong(int num, int count){
    int sum = 0,rem,num2 = num;
    while(num > 0){
        rem = num%10;
        sum += (int)pow(rem,count);
        num = num/10;
    }
    if(sum == num2){
        printf("%d is an Armstrong number",num2);
    }
    else{
        printf("%d is an not an Armstrong number",num2);
    }
}

int countDigits(int num){
    int count = 0;
    while(num > 0){
        count++;
        num = num/10;
    }
    return count;
}

int main(){

    int buffer[2],num;
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
        int c = countDigits(num);
        checkArmstrong(num,c);
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