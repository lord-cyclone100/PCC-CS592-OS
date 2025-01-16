#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    pid_t pid;
    int buffer[2];
    char str[100];
    pipe(buffer);
    pid = fork();
    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        close(buffer[1]);
        int letterCount = 0,numCount = 0, spCharCount = 0;
        read(buffer[0],str,sizeof(str));
        for(int i=0;str[i] != '\0';i++){
            if((str[i]>='A' && str[i]<='Z') || (str[i]>='a' && str[i]<='z')){
                letterCount++;
            }
            else if (str[i]>='0' && str[i]<='9'){
                numCount++;
            }
            else{
                spCharCount++;
            }
        }
        printf("No of alphabets : %d\nNo of digits : %d\nNo of special characters : %d\n",letterCount,numCount,spCharCount);
        close(buffer[0]);
    }
    else{
        close(buffer[0]);
        printf("Enter a string:");
        scanf("%s",str);
        write(buffer[1],str,strlen(str)+1);
        close(buffer[1]);
        wait(NULL);
    }
    return 0;
}