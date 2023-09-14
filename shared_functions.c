#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "shared_functions.h"

SharedData shared_data;  // Definition of the shared data structure
pthread_mutex_t data_lock;  // Mutex for data synchronisation
pthread_mutex_t count_lock;  // Mutex for readers count synchronisation
int readers_count = 0;  // Readers count variable

/*
 *
 * Function executed by the incrementer threads.
 *
 */ 
void* incrementer(void* arg) 
{
    int id = *(int*)arg;
    pthread_mutex_lock(&data_lock);
    shared_data.sum++;
    shared_data.last_incrementer_id = id;
    shared_data.num_incrementers++;

    printf("Incrementer %d set sum = %d\n", id, shared_data.sum);
    pthread_mutex_unlock(&data_lock);
    pthread_exit(NULL);
}

/*
 *
 * Function executed by the decrementer threads.
 *
 */ 
void* decrementer(void* arg) 
{
    int id = *(int*)arg;
    pthread_mutex_lock(&data_lock);
    shared_data.sum--;
    shared_data.last_decrementer_id = id;
    shared_data.num_decrementers++;

    printf("Decrementer %d set sum = %d\n", id, shared_data.sum);
    pthread_mutex_unlock(&data_lock);
    pthread_exit(NULL);
}

/*
 *
 * Function executed by the reader threads.
 *
 */ 
void* reader(void* arg) 
{
    int id = *(int*)arg;

    pthread_mutex_lock(&count_lock);
    readers_count++;

    if (readers_count == 1) 
    {
        pthread_mutex_lock(&data_lock);
    }

    pthread_mutex_unlock(&count_lock);
    printf("Reader %d got %d\n", id, shared_data.sum);

    pthread_mutex_lock(&count_lock);
    readers_count--;

    if (readers_count == 0) 
    {
        pthread_mutex_unlock(&data_lock);
    }

    pthread_mutex_unlock(&count_lock);
    pthread_exit(NULL);
}