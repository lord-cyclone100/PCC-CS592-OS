#include <stdio.h>

int countDigits(int num){
    int count = 0;
    while(num > 0){
        count++;
        num = num/10;
    }
    return count;
}

int main(){

    int num,isprime=1;
    printf("Enter a number:");
    scanf("%d",&num);
    int c = countDigits(num);
        printf("%d",c);

    return 0;
}