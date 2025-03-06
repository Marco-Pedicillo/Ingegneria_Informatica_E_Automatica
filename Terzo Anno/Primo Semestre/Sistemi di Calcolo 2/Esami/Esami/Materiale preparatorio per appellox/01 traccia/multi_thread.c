#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 5
#define THREAD_COUNT 4
#define ITERATION_COUNT 10
#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    int idx;
    int role;
} thread_args_t;

int buffer[BUFFER_LENGTH];
int write_index, read_index;

/**
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */

sem_t sem_filled;
sem_t sem_empty;
sem_t sem_read;
sem_t sem_write;


/***/


void producer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {
        int value = idx*ITERATION_COUNT + i;

        ret = sem_wait(&sem_filled);
        if(ret) handle_error("errore wait");
        ret = sem_wait(&sem_write);
        if(ret) handle_error("errore wait");

        buffer[write_index] = value;
        write_index = (write_index + 1) % BUFFER_LENGTH;

        ret = sem_post(&sem_write);
        if(ret) handle_error("errore post");
        ret = sem_post(&sem_empty);
        if(ret) handle_error("errore post");

        printf("[Thread #%d] inserito %d nel buffer\n", idx, value);
     }
}

void consumer_routine(int idx) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/multi-cons inserendo operazioni sui
     *   semafori ove necessario
     * - gestire gli errori
     *
     */

     int i, ret;
     for (i = 0; i < ITERATION_COUNT; i++) {

        ret = sem_wait(&sem_empty);
        if(ret) handle_error("errore wait");
        ret = sem_wait(&sem_read);
        if(ret) handle_error("errore wait");

        int value = buffer[read_index];
        read_index = (read_index + 1) % BUFFER_LENGTH;

        ret = sem_post(&sem_read);
        if(ret) handle_error("errore post");
        ret = sem_post(&sem_filled);
        if(ret) handle_error("errore post");

        printf("[Thread #%d] letto %d dal buffer\n", idx, value);
     }
}


void *thread_routine(void *args) {

    thread_args_t *thread_args = (thread_args_t*)args;
    if (thread_args->role == PROD_ROLE) {
        producer_routine(thread_args->idx);
    } else if (thread_args->role == CONS_ROLE) {
        consumer_routine(thread_args->idx);
    } else {
        printf("[Thread #%d] ruolo sconosciuto: %d\n", thread_args->idx, thread_args->role);
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {

    int ret;

    // inizializzazioni
    read_index = write_index = 0;

    /**
     * COMPLETARE QUI
     *
     * Obiettivi
     * - inizializzare i semafori dichiarati
     * - gestire gli errori
     */

    ret = sem_init(&sem_filled, 0, BUFFER_LENGTH);
    if(ret == -1) handle_error("errore init");
    ret = sem_init(&sem_empty, 0, 0);
    if(ret == -1) handle_error("errore init");
    ret = sem_init(&sem_read, 0, 1);
    if(ret == -1) handle_error("errore init");
    ret = sem_init(&sem_write, 0, 1);
    if(ret == -1) handle_error("errore init");

    /***/

    /**
     * COMPLETARE QUI
     *
     * Obiettivi: creazione thread
     * - ogni thread deve invocare la funzione thread_routine()
     * - gli argomenti per il thread devono essere specificati
     *   all'interno di una struttura thread_args_t
     * - il campo role può assumere come valori PROD_ROLE o CONS_ROLE
     * - ogni thread ha un valore di idx diverso tra 0 e THREAD_COUNT-1
     * - ci dovranno essere THREAD_COUNT/2 thread con ruolo produttore
     *   ed altrettanti con ruolo consumatore (THREAD_COUNT è pari)
     * - gestire glie errori
     * - N.B.: si tenga presente che successivamente il programma
     *   dovrà attendere la terminazione di ogni thread
     * 
     */

    pthread_t threads[THREAD_COUNT];
    int i;
    for(i=0; i<THREAD_COUNT; i++){
        thread_args_t* arg = calloc(1, sizeof(thread_args_t));
        arg->idx = i;
        if(i < THREAD_COUNT / 2)
            arg->role = CONS_ROLE;
        else
            arg->role = PROD_ROLE;

        ret = pthread_create(&threads[i], NULL, thread_routine, arg);
        if(ret) handle_error("errore thread create");
    }


    /***/


    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - attendere la terminazione dei thread lanciati in precedenza
     * - gestire gli errori
     */

    for(i=0; i<THREAD_COUNT; i++){
        ret = pthread_join(threads[i], NULL);
        if(ret) handle_error("errore join");
    }

    /***/

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - rilasciare i semafori inizializzati in precedenza
     * - gestire gli errori
     */

    ret = sem_destroy(&sem_filled);
    if(ret) handle_error("errore destroy");
    ret = sem_destroy(&sem_empty);
    if(ret) handle_error("errore destroy");
    ret = sem_destroy(&sem_read);
    if(ret) handle_error("errore destroy");
    ret = sem_destroy(&sem_write);
    if(ret) handle_error("errore destroy");


    /***/

    printf("[Main Thread] operazioni completate\n");

    return EXIT_SUCCESS;
}
