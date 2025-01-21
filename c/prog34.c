#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>

#define NO_OF_FRIENDS 5
sem_t mutex;

void* readBook(void* args){
    int id = *(int*)args;
    while(1){
        sem_wait(&mutex);
        printf("Friend %d is reading the book\n",id);
        sleep(1);
        printf("Friend %d has finished reading the book\n",id);
        sem_post(&mutex);
        sleep(1);
    }
}

int main(){
    sem_init(&mutex,0,1);
    pthread_t friends[NO_OF_FRIENDS];
    for(int i=0;i<NO_OF_FRIENDS;i++){
        pthread_create(&friends[i],NULL,readBook,(int*)&i);
    }

    for(int i=0;i<NO_OF_FRIENDS;i++){
        pthread_join(friends[i],NULL);
    }
    return 0;
}