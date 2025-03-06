#include <unistd.h>
#include <sys/wait.h>
#include "common.h"

#define CHILD_COUNT 2
#define GRANDCHILD_COUNT 3

int main(int argc, char* argv[]) {
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi: creare CHILD_COUNT processi figlio
     * - usare il ciclo for seguente per creare CHILD_COUNT processi
     * - ogni figlio deve salvare la propria identità i (vedi specifica)
     * - gestire eventuali errori
     */
     
    pid_t pid;
    int i = 0, j = 0;
    for (; i < CHILD_COUNT; i++) {
        pid = fork();
        if(pid == -1) ERROR_HELPER(pid, "errore pid");
        if(pid == 0) break;
    }
    
    
    /**
     * COMPLETARE QUI
     * 
     * Obiettivi
     * - ognuno dei processi figli deve a sua volta creare altri
     *   GRANDCHILD_COUNT processi figli (che qui chiamiamo processi nipoti)
     *   ° i processi nipoti devono eseguire sleep(1)
     *   ° i processi figli devono attendere il termine di tutti i 
     *     nipoti
     * - il processo padre deve attendere il termine di tutti i figli
     * - usare la variabile i per distinguere il padre dai figli
     * - usare la variabile j per distinguere i figli dai nipoti
     * - gestire eventuali errori
     */
    
    if(i<CHILD_COUNT){
        printf("figlio %d iniziato\n", i);
        for(;j<GRANDCHILD_COUNT; j++){
            pid_t pid = fork();
            if(pid == -1) ERROR_HELPER(pid, "errore pid");
            if(pid == 0) break;
        }

        if(j<GRANDCHILD_COUNT){
            printf("nipote %d.%d iniziato\n", i, j);
            sleep(1);
            printf("nipote %d,%d terminato\n", i, j);
        }else{
            printf("[figlio %d] nipoti lanciati, aspetta la loro terminazione\n", i);
            for(j=0;j<GRANDCHILD_COUNT;j++){
                pid_t pid = wait(NULL);
                if(pid == -1) ERROR_HELPER(pid, "errore wait");
            }
            printf("[figlio %d] terminato\n", i);
        }
    }else{
        printf("[padre] figli lanciati, aspetta la loro terminazione\n");
        for(i=0; i<CHILD_COUNT; i++){
            pid_t pid = wait(NULL);
            if(pid == -1) ERROR_HELPER(pid, "errore wait");
        }
        printf("[padre] figli terminati\n");
    }
    
    return EXIT_SUCCESS;
}
