#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "common.h"

int send_over_pipe(int write_desc, char* buf, size_t data_len) {
    int ret, bytes_sent = 0;

	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - inviare sulla pipe tutti i data_len byte contenuti nel buffer buf 
     * - gestire eventuali interruzioni ed errori
     * - assicurarsi che tutti i byte siano stati scritti
     */

    while(bytes_sent < data_len){
        ret = write(write_desc, buf + bytes_sent, data_len - bytes_sent);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) ERROR_HELPER(ret, "errore send");
        bytes_sent += ret;
    }
	 
    return bytes_sent;
}

int read_from_pipe(int read_desc, char* buf, size_t buf_len) {
    int ret, bytes_read = 0;
    
	/**
	 * COMPLETARE QUI
     *
     * Obiettivi:
	 * - leggere un messaggio dalla pipe e salvarlo nel buffer buf
     * - gestire eventuali interruzioni ed errori
     * - salvare il numero di byte ricevuti nella variabile 'bytes_read'
     *   e il valore restituito da una singola lettura in 'ret' 
     * - gestire chiusure inattese della connessione da parte del
     *   client uscendo dal loop usato per la lettura
     * 
     * Si tenga a mente che l'ultimo byte valido in un messaggio (la
     * cui lunghezza NON è nota a priori) è il terminatore di riga '\n'.
	 **/
	 
    do{
        ret = read(read_desc, buf + bytes_read, 1);
        if(ret == 0) break;
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) ERROR_HELPER(ret, "errore recv");
    }while(buf[bytes_read++] != '\n');
    
    return bytes_read;
}

void child_loop(int write_desc, int read_desc) {    
    char buf[BUF_SIZE];
    
    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int num = rand() % MAX_NUM;
        sprintf(buf, "%d\n", num);
        send_over_pipe(write_desc, buf, strlen(buf));
        //printf("[figlio] %s", buf);
        
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[figlio] msg %d: %s\n", i, buf);
    }
}

void parent_loop(int read_desc, int write_desc) {    
    char buf[BUF_SIZE];
    
    int i;
    for (i = 0; i < NUM_MSG; ++i) {
        int bytes_read = read_from_pipe(read_desc, buf, sizeof(buf));
        buf[bytes_read-1] = '\0';
        printf("[padre]  msg %d: %s\n", i, buf);
        
        int num = atoi(buf);
        sprintf(buf, "%d\n", 2*num);
        send_over_pipe(write_desc, buf, strlen(buf));
    }   
}

int main(int argc, char* argv[]) {
    int ret, first_pipe[2], second_pipe[2];
    pid_t pid;
	
    srand(SEED);
    
	/**
     * COMPLETARE QUI
     *
     * Obiettivi:
	 * - creazione di due pipe: utilizzare 'first_pipe' e 'second_pipe':
     * - creazione processo figlio
     * - un processo userà 'first_pipe' per comunicare dati all'altro e
     *   'second_pipe' per ricevere dati, l'altro farà il viceversa
	 * - chiusura estremità pipe non utilizzate in padre e figlio
     * - il processo figlio chiama child_loop() che prende come 1° arg.
     *   il descrittore pipe in scrittura per inviare dati al padre e
     *   e come 2° arg. il descrittore pipe in lettura da cui ricevere
     *   dati dal padre
     * - il processo padre chiama parent_loop() che prende come 1° arg.
     *   il descrittore pipe in lettura per ricevere dati dal figlio e
     *   e come 2° arg. il descrittore pipe in scrittura per inviare
     *   dati al figlio
	 * - il padre deve attendere la terminazione del figlio per uscire
	 * - chiusura descrittori pipe in fase di uscita
     * - gestire eventuali errori
     */

    ret = pipe(first_pipe);
    if(ret) ERROR_HELPER(ret, "errore pipe1");
    ret = pipe(second_pipe);
    if(ret) ERROR_HELPER(ret, "errore pipe2");

    pid = fork();
    if(pid == -1) ERROR_HELPER(ret, "errore pid");
    if(pid == 0){
        ret = close(first_pipe[0]);
        if(ret) ERROR_HELPER(ret, "errore close pipe1 in lettura");
        ret = close(second_pipe[1]);
        if(ret) ERROR_HELPER(ret, "errore close pipe2 in scrittura");

        child_loop(first_pipe[1], second_pipe[0]);

        ret = close(first_pipe[1]);
        if(ret) ERROR_HELPER(ret, "errore close pipe1 in scrittura");
        ret = close(second_pipe[0]);
        if(ret) ERROR_HELPER(ret, "errore close pipe2 in lettura");

        exit(EXIT_SUCCESS);
    }else{
        ret = close(first_pipe[1]);
        if(ret) ERROR_HELPER(ret, "errore close pipe1 in scrittura");
        ret = close(second_pipe[0]);
        if(ret) ERROR_HELPER(ret, "errore close pipe2 in lettura");
        
        parent_loop(first_pipe[0], second_pipe[1]);

        ret = wait(NULL);
        if(ret) ERROR_HELPER(ret, "errore wait");
        
        ret = close(first_pipe[0]);
        if(ret) ERROR_HELPER(ret, "errore close pipe1 in lettura");
        ret = close(second_pipe[1]);
        if(ret) ERROR_HELPER(ret, "errore close pipe2 in scrittura");
    }
    
    return 0;
}
