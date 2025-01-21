#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int checkPalindrome(char str[]){
    for(int i=0;i<strlen(str);i++){
        if(str[i] != str[strlen(str)-1-i]){
            return 0;
        }
    }
    return 1;
}

int main(){

    pid_t pid;
    int buffer[2];
    char str[30];
    pipe(buffer);
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }

    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],str,sizeof(str));
        int pl = checkPalindrome(str);
        if(pl == 0){
            printf("%s is not a palindrome",str);
        }
        else{
            printf("%s is a palindrome",str);
        }
    }

    else{
        close(buffer[0]);
        printf("Enter a string : ");
        scanf("%s",str);
        write(buffer[1],&str,strlen(str)+1);
        close(buffer[1]);
        wait(NULL);
    }

    return 0;
}