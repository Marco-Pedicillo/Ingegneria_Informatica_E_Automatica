#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>
#include "common.h"

#define BUFFER_LENGTH 3
#define SEED 91735
#define CHILD_COUNT 3
#define READ_COUNT 9
#define WRITE_COUNT 6
#define PROD_ROLE 0
#define CONS_ROLE 1

typedef struct thread_args_s {
    int child_id;
    int role;
    int read_count;
    int write_count;
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

void enqueue(int x) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */
    int ret;
    ret = sem_wait(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore wait");
    
    buffer[write_index] = x;
    write_index = (write_index + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore post");
    
}

int dequeue() {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - completare l'implementazione secondo il paradigma
     *   single-prod/single-cons
     * - gestire gli errori
     *
     */
    int x;
   
    int ret;
    ret = sem_wait(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore wait");
    
    x = buffer[read_index];
    read_index = (read_index + 1) % BUFFER_LENGTH;

    ret = sem_post(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore post");
    
    return x;
}

void producer(int child_id, int write_count) {
    int i = 0, value;
    for (; i < write_count; i++) {
        value = rand();
        enqueue(value);
        printf("[Proc. figlio %d] Producer ha inserito elemento %d con valore %d\n", child_id, (i+1), value);
    }
}

void consumer(int child_id, int read_count) {
    int i = 0, value;
    for (; i < read_count; i++) {
        value = dequeue();
        printf("[Proc. figlio %d] Consumer ha letto elemento %d con valore %d\n", child_id, (i+1), value);
    }
}

void *thread_routine(void *args) {
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - sulla base dei valori dei campi della struttura data passata come
     *   argomento, questa funzione deve invocare o la funzione producer()
     *   oppure la funzione consumer(), passando loro i parametri opportuni
     * - prima di invocare la funzione consumer(), verificare che il valore
     *   da passare per il suo argomento read_count non causi una attesa
     *   infinita da parte del consumer, e in tal caso ricalibrarne il
     *   valore in modo che vengano letti tutti e soli gli elementi
     *   effettivamente inseriti dal producer
     * - uscire dal thread
     *
     */

    thread_args_t* arg = (thread_args_t*)args;

    if(arg->role == PROD_ROLE)
        producer(arg->child_id, arg->write_count);
    else if(arg->role == CONS_ROLE){
        if(arg->read_count > arg->write_count) arg->read_count = arg->write_count;
        consumer(arg->child_id, arg->read_count);
    }else{
        printf("ruolo sconosciuto: %d\n", arg->role);
    }
     
     pthread_exit(NULL);
}

void child_routine(int child_id) {
    srand(SEED);
    
    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - inizializzare i semafori necessari
     * - creare un thread producer ed uno consumer; entrambi devono eseguire in 
     *   parallelo la funzione thread_routine(); per ognuno, preparare 
     *   un'istanza di struttura dati thread_args_t assegnando ai suoi campi dei
     *   valori opportuni (vedere le macro definite all'inizio di questo 
     *   sorgente)
     * - dopo aver creato questi due thread, il main thread deve attenderne la
     *   terminazione
     * - successivamente, il main thread deve rilasciare tutte le risorse da lui
     *   allocate
     * - gestire gli errori
     *
     */
    int ret;

    ret = sem_init(&sem_filled, 0, BUFFER_LENGTH);
    if(ret) ERROR_HELPER(ret, "errore init");
    ret = sem_init(&sem_empty, 0, 0);
    if(ret) ERROR_HELPER(ret, "errore init");

    pthread_t thread_prod, thread_cons;

    thread_args_t* arg_prod = calloc(1, sizeof(thread_args_t));
    thread_args_t* arg_cons = calloc(1, sizeof(thread_args_t));

    arg_prod->child_id = child_id;
    arg_prod->read_count = READ_COUNT;
    arg_prod->write_count = WRITE_COUNT;
    arg_prod->role = PROD_ROLE;

    arg_cons->child_id = child_id;
    arg_cons->read_count = READ_COUNT;
    arg_cons->write_count = WRITE_COUNT;
    arg_cons->role = CONS_ROLE;

    ret = pthread_create(&thread_prod, NULL, thread_routine, arg_prod);
    if(ret) ERROR_HELPER(ret, "errore pcreate");
    ret = pthread_create(&thread_cons, NULL, thread_routine, arg_cons);
    if(ret) ERROR_HELPER(ret, "errore pcreate");

    ret = pthread_join(thread_prod, NULL);
    if(ret) ERROR_HELPER(ret, "errore join");
    ret = pthread_join(thread_cons, NULL);
    if(ret) ERROR_HELPER(ret, "errore join");

    free(arg_cons);
    free(arg_prod);

    ret = sem_destroy(&sem_filled);
    if(ret) ERROR_HELPER(ret, "errore destroy");
    ret = sem_destroy(&sem_empty);
    if(ret) ERROR_HELPER(ret, "errore destroy");

}

int main(int argc, char* argv[]) {
    
    // inizializzazioni
    read_index = write_index = 0;

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - creare CHILD_COUNT processi figlio in modo che vengano eseguiti in
     *   parallelo
     * - il processo figlio i-esimo deve eseguire la funzione child_routine()
     *   con argomento i
     * - dopo aver creato tutti i processi figlio, il processo padre deve 
     *   attenderne la terminazione
     * - gestire gli errori
     * - VINCOLO: il codice scritto non deve contenere istruzioni di tipo
     *   exit o return che causino la terminazione del processo; deve
     *   esserci solo la "return EXIT_SUCCESS;" già presente alla fine
     *
     */

    int i;
    pid_t pid;
    int ret;

    for(i=0; i<CHILD_COUNT; i++){
        pid = fork();
        if(pid == -1) ERROR_HELPER(pid, "errore pid");
        if(pid == 0){
            child_routine(i);
            break;
        }
    }

    if(i == CHILD_COUNT){
        for(i=0; i<CHILD_COUNT; i++){
            ret = wait(NULL);
            if(ret == -1) ERROR_HELPER(ret, "errore wait");
        }
        printf("terminato processo padre \n");
    }else{
        printf("terminato processo figlio %d\n", i);
    }
    
    return EXIT_SUCCESS;
}
