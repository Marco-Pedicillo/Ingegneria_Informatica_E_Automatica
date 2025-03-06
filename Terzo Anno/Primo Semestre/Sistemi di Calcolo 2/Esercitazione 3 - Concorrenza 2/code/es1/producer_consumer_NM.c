#include <string.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include <time.h>       // nanosleep()

#define BUFFER_SIZE         128
#define INITIAL_DEPOSIT     0
#define MAX_TRANSACTION     1000
#define NUM_CONSUMERS       2
#define NUM_PRODUCERS       4
#define PRNG_SEED           0

#define NUM_OPERATIONS      400
#define OPS_PER_CONSUMER    (NUM_OPERATIONS/NUM_CONSUMERS)
#define OPS_PER_PRODUCER    (NUM_OPERATIONS/NUM_PRODUCERS)

// we use the preprocessor to check if our parameters are okay
#if OPS_PER_CONSUMER*NUM_CONSUMERS != OPS_PER_PRODUCER*NUM_PRODUCERS
#error "Choose NUM_CONSUMERS and NUM_PRODUCERS so that we get exactly NUM_OPERATIONS operations"
#endif

sem_t sem_vuoto, sem_pieno;
sem_t sem_write;
sem_t sem_read;

// struct used to specify arguments for a thread
typedef struct {
    int threadId;
    int numOps;
} thread_args_t;

// shared data
int transactions[BUFFER_SIZE];
int deposit = INITIAL_DEPOSIT;
int read_index, write_index;

// generates a number between -MAX_TRANSACTION and +MAX_TRANSACTION
static inline int performRandomTransaction() {
    struct timespec pause = {0};
    pause.tv_nsec = 10000000; // 10 ms (100*10^6 ns)
    nanosleep(&pause, NULL);
    //return 1; /** This permits to easily check the correctnes of the exercize **/ 
    int amount = rand() % (2 * MAX_TRANSACTION); // {0, ..., 2*MAX_TRANSACTION - 1}
    if (amount >= MAX_TRANSACTION) {
        return MAX_TRANSACTION - (amount+1); // {-MAX_TRANSACTION, ..., -1}
    } else { 
        return amount + 1; // {1, ..., MAX_TRANSACTION}
    }
}

// producer thread
void* performTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting producer thread %d\n", args->threadId);

    while (args->numOps > 0) {
        // produce the item
        int currentTransaction = performRandomTransaction();

        if(sem_wait(&sem_vuoto)) handle_error("Produttore: errore sem_wait vuoto");
        if(sem_wait(&sem_write)) handle_error("Produttore: errore sem_wait write");

        // write the item and update write_index accordingly
        transactions[write_index] = currentTransaction;
        write_index = (write_index + 1) % BUFFER_SIZE;

        if(sem_post(&sem_write)) handle_error("Produttore: errore sem_post write");
        if(sem_post(&sem_pieno)) handle_error("Produttore: errore sem_post pieno");
        

        args->numOps--;
        //printf("P %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

void* processTransactions(void* x) {
    thread_args_t* args = (thread_args_t*)x;
    printf("Starting consumer thread %d\n", args->threadId);

    while (args->numOps > 0) {
        if(sem_wait(&sem_pieno)) handle_error("Consumatore: errore sem_wait");
        if(sem_wait(&sem_read)) handle_error("Produttore: errore sem_wait read");

        // consume the item and update (shared) variable deposit
        deposit += transactions[read_index];
        read_index = (read_index + 1) % BUFFER_SIZE;
        if (read_index % 100 == 0)
			printf("After the last 100 transactions balance is now %d.\n", deposit);
        
        if(sem_post(&sem_read)) handle_error("Produttore: errore sem_post read");
        if(sem_post(&sem_vuoto)) handle_error("Consumatore: errore sem_post");

        args->numOps--;
        //printf("C %d\n", args->numOps);
    }

    free(args);
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    printf("Welcome! This program simulates financial transactions on a deposit.\n");
    printf("\nThe maximum amount of a single transaction is %d (negative or positive).\n", MAX_TRANSACTION);
    printf("\nInitial balance is %d. Press CTRL+C to quit.\n\n", INITIAL_DEPOSIT);

    // initialize read and write indexes
    read_index  = 0;
    write_index = 0;

    if(sem_init(&sem_pieno,0 , 0)) handle_error("init error sem_pieno");
    if(sem_init(&sem_vuoto,0 , BUFFER_SIZE)) handle_error("init error sem_vuoto");
    if(sem_init(&sem_write,0 , 1)) handle_error("init error sem_write");
    if(sem_init(&sem_read,0 , 1)) handle_error("init error sem_read");

    // set seed for pseudo-random number generator: we use this to make
    // this code yield the same result across different runs, as long
    // as they are race-free and you make no mistakes :-)
    srand(PRNG_SEED); 
    
    int ret;
    pthread_t producer[NUM_PRODUCERS], consumer[NUM_CONSUMERS];

    int i;
    for (i=0; i<NUM_PRODUCERS; ++i) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = i;
        arg->numOps = OPS_PER_PRODUCER;

        ret = pthread_create(&producer[i], NULL, performTransactions, arg);
        if (ret != 0) { fprintf(stderr, "Error %d in pthread_create\n", ret); exit(EXIT_FAILURE); }
    }

    int j;
    for (j=0; j<NUM_CONSUMERS; ++j) {
        thread_args_t* arg = malloc(sizeof(thread_args_t));
        arg->threadId = j;
        arg->numOps = OPS_PER_CONSUMER;

        ret = pthread_create(&consumer[j], NULL, processTransactions, arg);
        if (ret != 0) { fprintf(stderr, "Error %d in pthread_create\n", ret); exit(EXIT_FAILURE); }
    }

    // join on threads
    for (i=0; i<NUM_PRODUCERS; ++i) {
        ret = pthread_join(producer[i], NULL);
        if (ret != 0) { fprintf(stderr, "Error %d in pthread_join\n", ret); exit(EXIT_FAILURE); }
    }

    for (j=0; j<NUM_CONSUMERS; ++j) {
        ret = pthread_join(consumer[j], NULL);
        if (ret != 0) { fprintf(stderr, "Error %d in pthread_join\n", ret); exit(EXIT_FAILURE); }
    }

    printf("Final value for deposit: %d\n", deposit);

    sem_destroy(&sem_vuoto);
    sem_destroy(&sem_pieno);
    sem_destroy(&sem_write);
    sem_destroy(&sem_read);

    exit(EXIT_SUCCESS);
}
