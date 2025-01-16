#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCER_COUNT 3
#define CONSUMER_COUNT 3

sem_t mutex, full, empty;
int buffer[BUFFER_SIZE], in = 0, out = 0;

void* producer(){
	int item;
	while(1){
		item = rand()%10;
		sem_wait(&empty);
		sem_wait(&mutex);
		buffer[in] = item;
		printf("Producer produced item %d at location %d\n",item,in);
		in = (in+1)%BUFFER_SIZE;
		sem_post(&mutex);
		sem_post(&full);
		sleep(1);
	}
}
void* consumer(){
	int item;
	while(1){
		sem_wait(&full);
		sem_wait(&mutex);
		item = buffer[out];
		printf("Consumer consumed item %d at location %d\n",item,out);
		out = (out+1)%BUFFER_SIZE;
		sem_post(&mutex);
		sem_post(&empty);
		sleep(1);
	}
}

int main(){

	pthread_t producers[PRODUCER_COUNT], consumers[CONSUMER_COUNT];
	sem_init(&mutex,0,1);
	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);

	for(int i=0;i<PRODUCER_COUNT;i++){
		pthread_create(&producers[i],NULL,producer,NULL);
	}

	for(int i=0;i<CONSUMER_COUNT;i++){
		pthread_create(&consumers[i],NULL,consumer,NULL);
	}

	for(int i=0;i<PRODUCER_COUNT;i++){
		pthread_join(producers[i],NULL);
	}

	for(int i=0;i<CONSUMER_COUNT;i++){
		pthread_join(consumers[i],NULL);
	}

	return 0;
}
