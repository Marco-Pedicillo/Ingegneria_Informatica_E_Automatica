#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define SEED 91735

// numero produttori/consumatori/buffer
#define N 3

// dimensione del singolo buffer
#define BUFFER_LENGTH 3

// numero elementi inseriti da ogni produttore/letti da ogni consumatore
#define ELEMENT_COUNT 5

#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    // identificativo del produttore/consumatore, varia tra 0 e N-1
    int id;
    
    // specifica se il thread è un produttore (PROD_ROLE) o un 
    // consumatore (CONS_ROLE)
    int role;
    
    // numero elementi inseriti nel/letti dal buffer
    int element_count; 
} thread_args_t;

/**
 * buffer[i] è il buffer dove l'i-esimo produttore scrive e l'i-esimo 
 * consumatore legge, i varia tra 0 e N-1
 * 
 * buffer[i][j] è il j-esimo elemento del buffer i-esimo, j varia tra 0 
 * e BUFFER_LENGTH-1
 */
int buffer[N][BUFFER_LENGTH];

/**
 * write_index[i] è l'indice di scrittura del buffer i-esimo
 * read_index[i] è l'indice di lettura del buffer i-esimo
 * i varia tra 0 e N-1
 */
int write_index[N], read_index[N];

/**
 * COMPLETARE QUI
 *
 * Obiettivi:
 * - dichiarare i semafori necessari
 *
 */

sem_t sem_filled[N];
sem_t sem_empty[N];


/**
 * Questa funzione gestisce l'enqueue dell'elemento x nel buffer id
 */
void enqueue(int id, int x) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - implementare la funzione secondo il paradigma single-prod/single-cons
     * - gestire gli errori
     *
     */

    int ret;

    ret = sem_wait(&sem_filled[id]);
    if(ret) ERROR_HELPER(ret, "errore wait");

    buffer[id][write_index[id]] = x;
    write_index[id] = (write_index[id] + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_empty[id]);
    if(ret) ERROR_HELPER(ret, "errore post");

}

/**
 * Questa funzione gestisce la dequeue dal buffer id
 */
int dequeue(int id) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - implementare la funzione secondo il paradigma single-prod/single-cons
     * - gestire gli errori
     *
     */
    int ret, x;

    ret = sem_wait(&sem_empty[id]);
    if(ret) ERROR_HELPER(ret, "errore wait");

    x = buffer[id][read_index[id]];
    read_index[id] = (read_index[id] + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_filled[id]);
    if(ret) ERROR_HELPER(ret, "errore post");

    return x;

}

void *thread_routine(void *args) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - sulla base dei valori in args, implementare la logica del 
     *   produttore o del consumatore
     *   * il produttore con identificativo id deve fare element_count 
     *     enqueue() nel buffer id
     *   * per scegliere il valore dell'elemento da inserire, usare la 
     *     funzione rand()
     *   * il consumatore con identificativo id deve fare element_count 
     *     dequeue() dal buffer id
     * - rilasciare le risorse occupate dal thread
     * - uscire dal thread
     *
     */

    int i, value;
    thread_args_t* arg = (thread_args_t*)args;
    
    for(i=0; i< arg->element_count; i++){
        if(arg->role == PROD_ROLE){
            value = rand();
            enqueue(arg->id, value);
            printf("Il producer %d ha inserito nel buffer l'elemento numero %d con valore %d\n", arg->id, (i+1), value);
        }else if(arg->role == CONS_ROLE){
            value = dequeue(arg->id);
            printf("Il consumer %d ha letto dal buffer l'elemento numero %d con valore %d\n", arg->id, (i+1), value);
        }
    }

    free(args);
    pthread_exit(NULL);
     
}

void *orchestrator_routine(void *arg) {
    
    int role = *(int*)arg;
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - creare ed avviare in parallelo N thread
     * - ogni thread deve eseguire la funzione thread_routine()
     * - per ogni thread, preparare un'istanza di thread_args_t
     *   * il thread i-esimo deve avere id pari ad i
     *   * il ruolo è dato dall'argomento di input di questa funzione
     *   * il numero di elementi è dato dalla macro ELEMENT_COUNT
     * - dopo aver creato questi thread, attenderne il termine
     * - gestire gli errori
     * - uscire dal thread
     * 
     */

    int i, ret;
    pthread_t threads[N];
    
    for(i=0; i<N; i++){
        thread_args_t* arg = calloc(1, sizeof(thread_args_t));
        arg->id = i;
        arg->element_count = ELEMENT_COUNT;
        arg->role = role;

        ret = pthread_create(&threads[i], NULL, thread_routine, arg);
        if(ret) ERROR_HELPER(ret, "errore create");
        printf("Creato thread %d con ruolo %d\n", i, role);
    }

    for(i=0; i<N; i++){
        ret = pthread_join(threads[i], NULL);
        if(ret) ERROR_HELPER(ret, "errore join");
        printf("Terminato thread %d con ruolo %d\n", i, role);
    }

    pthread_exit(NULL);
    
}

int main(int argc, char* argv[]) {
    
    srand(SEED);
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - inizializzare gli indici di lettura/scrittura dei buffer
     * - inizializzare i semafori
     * - creare ed avviare in parallelo i due thread orchestratori
     *   * uno deve avere ruolo PROD_ROLE, l'altro CONS_ROLE
     *   * entrambi devono eseguire la funzione orchestrator_routine()
     *   * suggerimento: utilizzare una variabile int per il ruolo
     * - dopo aver creato questi thread, attenderne il termine
     * - rilasciare le risorse create in questa funzione
     * - gestire gli errori
     *
     */

    int ret, i;

    for(i=0; i<N; i++){
        read_index[i] = write_index[i] = 0;

        ret = sem_init(&sem_filled[i], 0, BUFFER_LENGTH);
        if(ret) ERROR_HELPER(ret, "errore init");
        ret = sem_init(&sem_empty[i], 0, 0);
        if(ret) ERROR_HELPER(ret, "errore init");
    }

    int prod_role = PROD_ROLE;
    pthread_t prod_orchestrator;
    ret = pthread_create(&prod_orchestrator, NULL, orchestrator_routine, &prod_role);
    if(ret) ERROR_HELPER(ret, "errore create");
    printf("Creato orchestratore produttori\n");

    int cons_role = CONS_ROLE;
    pthread_t cons_orchestrator;
    ret = pthread_create(&cons_orchestrator, NULL, orchestrator_routine, &cons_role);
    if(ret) ERROR_HELPER(ret, "errore create");
    printf("Creato orchestratore consumatori\n");

    ret = pthread_join(prod_orchestrator, NULL);
    if(ret) ERROR_HELPER(ret, "errore join");
    printf("Terminato orchestratore produttori\n");

    ret = pthread_join(cons_orchestrator, NULL);
    if(ret) ERROR_HELPER(ret, "errore join");
    printf("Terminato orchestratore consumatori\n");

    for(i=0; i<N; i++){
        ret = sem_destroy(&sem_filled[i]);
        if(ret) ERROR_HELPER(ret, "errore destroy");

        ret = sem_destroy(&sem_empty[i]);
        if(ret) ERROR_HELPER(ret, "errore destroy");
    }
    
    return EXIT_SUCCESS;
}
