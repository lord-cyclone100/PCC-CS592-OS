#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int a[15][15],b[15][15],c[15][15],r1,c1,r2,c2;

void* inputMatrix(){
    pthread_mutex_lock(&mutex);
    printf("Enter the number of rows and columns of 1st matrix: ");
    scanf("%d %d",&r1,&c1);
    printf("Enter the 1st matrix elements : ");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            scanf("%d",&a[i][j]);
        }
    }
    printf("Enter the number of rows and columns of 2nd matrix: ");
    scanf("%d %d",&r2,&c2);
    printf("Enter the 2nd matrix elements : ");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            scanf("%d",&b[i][j]);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void* calcDifference(){
    pthread_mutex_lock(&mutex);
    
    if(r1 != r2 || c1 != c2){
        printf("The matrices is not of same order\n");
        exit(1);
    }

    printf("1st matrix : \n");
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }
    printf("2nd matrix : \n");
    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",b[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<r1;i++){
        for(int j=0;j<c1;j++){
            c[i][j] = a[i][j] - b[i][j];
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){
    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,inputMatrix,NULL);
    pthread_create(&thread2,NULL,calcDifference,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("Difference\n");

    for(int i=0;i<r2;i++){
        for(int j=0;j<c2;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
}