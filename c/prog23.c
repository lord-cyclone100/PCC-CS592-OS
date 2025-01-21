#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int r,c,a[15][15],isSymmetric=1;

void* matrixInitialize(){
    pthread_mutex_lock(&mutex);
    printf("Enter the no of rows and columns : ");
    scanf("%d %d",&r,&c);
    printf("Enter the elements : ");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&a[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* checkSymmetric(){
    pthread_mutex_lock(&mutex);
    if(r != c){
        printf("The entered matrix is not a square matrix");
        exit(1);
    }
    printf("Entered matrix : \n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            if(a[i][j] != a[j][i]){
                isSymmetric = 0;
                break;
            }
        }
        if(isSymmetric == 0){
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1,NULL,matrixInitialize,NULL);
    pthread_create(&thread2,NULL,checkSymmetric,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    if(isSymmetric){
        printf("The entered matrix is symmetric");
    }
    else{
        printf("The entered matrix is not symmetric");
    }
    return 0;
}