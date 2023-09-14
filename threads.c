/*
 * COSC330 Assignment 02 - By Vladimir Ovechkin
 * This program demonstrates the readers and writers synchronisation
 * problem by ensuring writers have exclusive access to data over readers.
 *
 * To compile this program, use the "make" command from the Terminal.
 * To run this program, enter "make run".
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "shared_functions.h"

int main() 
{
    srand(time(NULL));
    int num_incrementers = rand() % 10 + 1; // Random number of incrementers (1-10)
    int num_decrementers = rand() % 10 + 1; // Random number of decrementers (1-10)
    int num_readers = rand() % 10 + 1;      // Random number of readers (1-10)

    pthread_t incrementer_threads[num_incrementers];
    pthread_t decrementer_threads[num_decrementers];
    pthread_t reader_threads[num_readers];

    pthread_mutex_init(&data_lock, NULL);  // Initialise the data mutex
    pthread_mutex_init(&count_lock, NULL);  // Initialise the count mutex

    for (int i = 0; i < num_incrementers; i++) 
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&incrementer_threads[i], NULL, incrementer, id);
    }

    for (int i = 0; i < num_decrementers; i++) 
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&decrementer_threads[i], NULL, decrementer, id);
    }

    for (int i = 0; i < num_readers; i++) 
    {
        int* id = malloc(sizeof(int));
        *id = i;
        pthread_create(&reader_threads[i], NULL, reader, id);
    }

    for (int i = 0; i < num_incrementers; i++) 
    {
        pthread_join(incrementer_threads[i], NULL);
    }

    for (int i = 0; i < num_decrementers; i++) 
    {
        pthread_join(decrementer_threads[i], NULL);
    }

    for (int i = 0; i < num_readers; i++) 
    {
        pthread_join(reader_threads[i], NULL);
    }

    printf("There were %d readers, %d incrementers, and %d decrementers\n", num_readers, num_incrementers, num_decrementers);
    printf("The final state of the data is:\n");
    printf("    last incrementer %d\n", shared_data.last_incrementer_id);
    printf("    last decrementer %d\n", shared_data.last_decrementer_id);
    printf("    total writers %d\n", shared_data.num_incrementers + shared_data.num_decrementers);
    printf("    sum %d\n", shared_data.sum);

    pthread_mutex_destroy(&data_lock);  // Destroy the data mutex
    pthread_mutex_destroy(&count_lock);  // Destroy the count mutex

    return 0;
}