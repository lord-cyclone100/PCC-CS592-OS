#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int a,b,c;
sem_t mutex;

void* receiveFirstNum(){
    printf("Enter the value of a : ");
    scanf("%d",&a);
    sem_post(&mutex);
}

void* receiveSecondNum(){
    sem_wait(&mutex);
    printf("Enter the value of b : ");
    scanf("%d",&b);
    sem_post(&mutex);
}

void* calcResult(){
    sem_wait(&mutex);
    printf("Sum : %d",a+b);
    sem_post(&mutex);
}

int main(){
    sem_init(&mutex,0,0);
    pthread_t thread1,thread2,thread3;

    pthread_create(&thread1,NULL,&receiveFirstNum,NULL);
    pthread_create(&thread2,NULL,&receiveSecondNum,NULL);
    pthread_create(&thread3,NULL,&calcResult,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);

    return 0;
}