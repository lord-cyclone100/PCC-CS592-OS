#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){

    int buffer[2];
    char str[50];
    pid_t pid;
    pipe(buffer);
    pid = fork();

    if(pid == -1){
        printf("Error in fork");
        exit(1);
    }
    if(pid == 0){
        close(buffer[1]);
        read(buffer[0],&str,sizeof(str));
        int v_count = 0,c_count = 0;
        for(int i=0;str[i] != '\0';i++){
            if(str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U' || str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'){
                v_count++;
            }
            else{
                c_count++;
            }
        }
        printf("Number of vowels : %d\n",v_count);
        printf("Number of consonants : %d\n",c_count);
        close(buffer[0]);
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