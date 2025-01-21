#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define PHILOSOPHER_COUNT 5
#define CHOPSTICK_COUNT 5

sem_t chopsticks[CHOPSTICK_COUNT];

void* diningPhilosopher(void* args){
    int id = *(int*)args;
    while(1){
        
        sem_wait(&chopsticks[id]);
        sem_wait(&chopsticks[(id+1)%CHOPSTICK_COUNT]);
        printf("Philosopher %d is now eating\n",id);
        sleep(1);
        sem_post(&chopsticks[id]);
        sem_post(&chopsticks[(id+1)%CHOPSTICK_COUNT]);
        printf("Philosopher %d is now thinking\n",id);
        sleep(1);
    }
}

int main(){
    pthread_t philosophers[PHILOSOPHER_COUNT];
    for(int i=0;i<CHOPSTICK_COUNT;i++){
        sem_init(&chopsticks[i],0,1);
    }
    for(int i=0;i<PHILOSOPHER_COUNT;i++){
        philosophers[i]=i;
        pthread_create(&philosophers[i],NULL,&diningPhilosopher,(int*)&i);
    }
    for(int i=0;i<PHILOSOPHER_COUNT;i++){
        pthread_join(philosophers[i],NULL);
    }

    return 0;
}