#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int a[15][15],b[15][15],r,c;

void* inputMatrix(){
    pthread_mutex_lock(&mutex);
    printf("Enter the number of rows and columns : ");
    scanf("%d %d",&r,&c);
    printf("Enter the matrix elements : ");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            scanf("%d",&a[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* calcTranspose(){
    pthread_mutex_lock(&mutex);
    
    if(r != c){
        printf("The matrix is not a square matrix\n");
        exit(1);
    }

    printf("Original matrix : \n");
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            b[i][j] = a[j][i];
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,inputMatrix,NULL);
    pthread_create(&thread2,NULL,calcTranspose,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("Transpose\n");

    for(int i=0;i<r;i++){
        for(int j=0;j<c;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
}