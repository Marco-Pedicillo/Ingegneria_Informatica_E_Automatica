#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"

#define SEED    0
#define THREADS 4
#define ELEMS   (THREADS<<24)
#define MAGIC   (ELEMS>>8)
#define STEP    (ELEMS/THREADS)

typedef struct thread_args_s {
    int* counter;
    int* array;
    int item;
    int start;
    int end;
} thread_args_t;

int countOcc(int item, int* array, int start, int end) {
    int ret = 0;
    while (start < end) if (array[start++] == item) ++ret;
    return ret;
}

void* thread_routine(void *x) {
    thread_args_t* args = (thread_args_t*)x;
    
    *(args->counter) = countOcc(args->item, args->array, args->start, args->end);
        
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    int i, ret;
    
    srand(SEED);
    int item = rand() % MAGIC;
    
    printf("Item to find: %d\n", item);
    printf("Array size in memory: %ld KBs\n", ELEMS*sizeof(int)/1024);
    
    int* array = malloc(ELEMS*sizeof(int));
    for (i=0; i<ELEMS; ++i) array[i] = rand() % MAGIC;
    
    printf("Array initialized. Starting search...\n");
    
    /* COMPLETARE QUI
     * 
     * Panoramica:
     * Il programma processa il contenuto di 'array' in modo parallelo:
     * ogni thread processa una parte della struttura, e poi il main
     * thread aggrega i risultati calcolati dai singoli thread.
     * 
     * L'array viene diviso tra i thread in segmenti di 'STEP' elementi.
     * Il primo thread inizia dall'elemento 0 e ferma quando raggiunge
     * l'elemento STEP, che è il punto di partenza per il secondo.
     * 
     * Ogni thread scrive il risultato nella cella che gli è stata
     * riservata all'interno dell'array 'counters'. 
     * 
     * Obiettivi:
     * - creare 'THREADS' threads che eseguano la funzione 'thread_routine'
     * - argomenti per il thread i-esimo {0, 1, ..., THREADS-1}
     *    > 'counter': indirizzo in 'counters' dove salvare il risultato
     *    > 'array': array contenente i dati da processare
     *    > 'start': indice in 'array' da dove iniziare il processamento
     *    > 'end': indice in array dove arrestare la ricerca (nota bene:
     *             l'elemento in posizione 'end' NON verrà analizzato)
     *    > 'item': elemento da cercare (passare 'item' della riga 38)
     * - attendere esplicitamente la terminazione dei threads creati
     * - gestire eventuali interruzioni ed errori
     *  
     * */
    int counters[THREADS];
    pthread_t threads[THREADS];

    for(i=0; i<THREADS; i++){
        thread_args_t* arg = calloc(1, sizeof(thread_args_t));
        arg->array = array;
        arg->counter = &counters[i];
        arg->item = item;
        arg->start = i*STEP;
        arg->end = (i+1)*STEP;

        ret = pthread_create(&threads[i], NULL, thread_routine, arg);
        if(ret) ERROR_HELPER(ret, "errore create");
    }

    for(i=0; i<THREADS; i++){
        ret = pthread_join(threads[i], NULL);
        if(ret) ERROR_HELPER(ret, "errore join");
    }

    
    int aggregated = 0;
    for (i=0; i<THREADS; ++i) aggregated += counters[i];
    
    printf("Computed result: %d\n", aggregated);
    printf("Expected result: %d\n", countOcc(item, array, 0, ELEMS));
    
    return 0;
}
