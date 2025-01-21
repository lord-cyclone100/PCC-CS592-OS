#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int n, arr[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* arrayInput(){
    pthread_mutex_lock(&mutex);
    printf("Enter the length of the array : ");
    scanf("%d",&n);
    printf("Enter array elements:");
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    printf("Original array : ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
    pthread_mutex_unlock(&mutex);
}

void* arraySort(){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<n-1;i++){
        int swapped = 0;
        for(int j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = 1;
            }
        }
        if(swapped == 0){
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

int main(){

    pthread_t thread1, thread2;

    pthread_create(&thread1,NULL,arrayInput,NULL);
    pthread_create(&thread2,NULL,arraySort,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    printf("\nSorted array : ");
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }

    return 0;
}