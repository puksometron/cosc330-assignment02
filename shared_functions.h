#ifndef SHARED_FUNCTIONS_H
#define SHARED_FUNCTIONS_H

typedef struct 
{
    int sum;
    int last_incrementer_id;
    int last_decrementer_id;
    int num_incrementers;
    int num_decrementers;
} SharedData;

extern SharedData shared_data;  // Declaration of the shared data structure
extern pthread_mutex_t data_lock;  // Declaration of the mutex for data synchronisation
extern pthread_mutex_t count_lock;  // Declaration of the mutex for readers count synchronisation
extern int readers_count;  // Declaration of the readers count variable

void* incrementer(void* arg);  // Function prototype for the incrementer thread function
void* decrementer(void* arg);  // Function prototype for the decrementer thread function
void* reader(void* arg);  // Function prototype for the reader thread function

#endif