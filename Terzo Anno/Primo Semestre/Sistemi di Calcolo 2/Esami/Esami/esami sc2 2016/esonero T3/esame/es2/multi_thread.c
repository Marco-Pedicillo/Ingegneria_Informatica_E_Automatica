#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 500
#define THREAD_COUNT 10
#define ITERATION_COUNT 50
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
sem_t sem_cs;


void enqueue(int x) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/single-cons
     * - gestire gli errori
     *
     */
     
    int ret;

    ret = sem_wait(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore wait");
    ret = sem_wait(&sem_cs);
    if(ret) ERROR_HELPER(ret, "errore wait");
    
    buffer[write_index] = x;
    write_index = (write_index + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_cs);
    if(ret) ERROR_HELPER(ret, "errore post");
    ret = sem_post(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore post");
	
}

int dequeue() {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   multi-prod/single-cons
     * - gestire gli errori
     *
     */
     
    int ret, x;

    ret = sem_wait(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore wait");
    
    x = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore post");
    
    return x;
}

void *thread_routine(void *args) {
    
    thread_args_t *thread_args = (thread_args_t*)args;
    
    int i = 0;
    for (; i < ITERATION_COUNT; i++) {
        if (thread_args->role == PROD_ROLE) {
            int value = thread_args->idx * i;
            enqueue(value);
            printf("[Thread #%d] inserito %d nel buffer\n", thread_args->idx, value);
        } else if (thread_args->role == CONS_ROLE) {
            int value = dequeue();
            printf("[Thread #%d] letto %d dal buffer\n", thread_args->idx, value);
        } else {
            printf("[Thread #%d] ruolo sconosciuto: %d\n", thread_args->idx, thread_args->role);
        }
    }
    
    free(thread_args);
    
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
    if(ret) ERROR_HELPER(ret, "errore init");
    ret = sem_init(&sem_empty, 0, 0);
    if(ret) ERROR_HELPER(ret, "errore init");
    ret = sem_init(&sem_cs, 0, 1);
    if(ret) ERROR_HELPER(ret, "errore init");
     
    
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi: lanciare THREAD_COUNT thread
     * - nota bene: successivamente bisogna attendere il termine di ogni 
     *   thread
     * - per ogni thread, preparare prima i parametri da passargli
     *  (struttura thread_args_t)
     * - l'idx deve essere diverso per ogni thread
     * - il role può assumere come valori PROD_ROLE o CONS_ROLE, ci deve 
     *   essere un solo consumatore, gli altri devono essere dei 
     *   produttori
     * - ogni thread lanciato deve eseguire la funzione thread_routine()
     * - una volta lanciato un thread, gestire gli errori
     */
    
    // lancio thread
    pthread_t threads[THREAD_COUNT];

    int i;
    for(i=0; i<THREAD_COUNT; i++){
        thread_args_t* arg = calloc(1, sizeof(thread_args_t));
        arg->idx = i;
        if(i==0) 
            arg->role = CONS_ROLE;
        else
            arg->role = PROD_ROLE;

        ret = pthread_create(&threads[i], NULL, thread_routine, arg);
        if(ret) ERROR_HELPER(ret, "errore create");
    }
    
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi: attendere il termine dei thread
     * - attendere il termine di ognuno dei THREAD_COUNT thread lanciati
     *   in precedenza
     * - gestire gli errori
     */

    for(i=0; i<THREAD_COUNT; i++){
        ret = pthread_join(threads[i], NULL);
        if(ret) ERROR_HELPER(ret, "errore join");
    }
    
    
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi: rilasciare i semafori inizializzati in precedenza
     * - per ogni semaforo rilasciato, gestire gli errori
     */

    ret = sem_destroy(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore destroy");
    ret = sem_destroy(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore destroy");
    ret = sem_destroy(&sem_cs);
    if(ret) ERROR_HELPER(ret, "errore destroy");
    
    printf("[Main Thread] operazioni completate\n");
    
    return EXIT_SUCCESS;
}
