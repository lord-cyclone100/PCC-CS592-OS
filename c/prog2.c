#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READER_COUNT 5
#define WRITER_COUNT 2

sem_t mutex,wrt;
int readers_num=0,write_data=0;

void* reader(){
    while(1){
        sem_wait(&mutex);
        readers_num++;
        printf("Reader entered\n");
        if(readers_num == 1){
            sem_wait(&wrt);
        }
        sem_post(&mutex);
        printf("Reader is reading %d\n",readers_num);
        sleep(1);
        sem_wait(&mutex);
        readers_num--;
        printf("Reader left\n");
        if(readers_num == 0){
            sem_post(&wrt);
        }
        sem_post(&mutex);
        sleep(1);
    }
}

void* writer(){
    while(1){
        sem_wait(&wrt);
        write_data++;
        printf("Writer entered\n");
        printf("Writer writing %d\n",write_data);
        sem_post(&wrt);
        printf("Writer left\n");
        sleep(1);
    }
}

int main(){

    pthread_t reader_grp[READER_COUNT], writer_grp[WRITER_COUNT];

    sem_init(&wrt,0,1);
    sem_init(&mutex,0,1);

    for(int i=0;i<READER_COUNT;i++){
        pthread_create(&reader_grp[i],NULL,reader,NULL);
    }
    for(int i=0;i<WRITER_COUNT;i++){
        pthread_create(&writer_grp[i],NULL,writer,NULL);
    }
    for(int i=0;i<READER_COUNT;i++){
        pthread_join(reader_grp[i],NULL);
    }
    for(int i=0;i<WRITER_COUNT;i++){
        pthread_join(writer_grp[i],NULL);
    }
    return 0;
}