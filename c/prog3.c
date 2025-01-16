#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>

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
        if(num%2 == 0){
            printf("%d is even\n",num);
        }
        else{
            printf("%d is odd\n",num);
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