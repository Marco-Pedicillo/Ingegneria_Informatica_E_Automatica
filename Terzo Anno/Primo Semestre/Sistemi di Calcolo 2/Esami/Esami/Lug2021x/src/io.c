#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#include "common.h"
#include "io.h"

int send_to_socket(int sd, const char *msg) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - usare il descrittore sd per inviare tutti i byte della stringa msg
     *   (incluso il terminatore di stringa \0)
     * - come valore di ritorno, restituire il numero di byte inviati (incluso
     *   il terminatore di stringa \0)
     * - gestire eventuali interruzioni, riprendendo l'invio da dove era stato
     *   interrotto
     * - gestire eventuali errori, terminando l'applicazione
     *
     */
    int ret;
    int bytes_sent = 0;

    while(bytes_sent < strlen(msg) + 1){
        ret = send(sd, msg + bytes_sent, (strlen(msg) + 1) - bytes_sent, 0);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("errore send");
        bytes_sent += ret;
    }
    printf("byte inviati: %d\n", bytes_sent);
    return bytes_sent;

}

int recv_from_socket(int sd, char *msg, int max_len) {

    /**
     * COMPLETARE QUI
     *
     * Obiettivi:
     * - usare il descrittore sd per ricevere una stringa da salvare nel buffer
     *   msg (incluso il terminatore di stringa \0); la lunghezza della stringa
     *   non è nota a priori, ma comunque minore di max_len;
     * - ricevere fino ad un massimo di max_len bytes (incluso il terminatore di
     *   stringa \0);
     * - come valore di ritorno, restituire il numero di byte ricevuti (escluso
     *   il terminatore di stringa \0)
     * - in caso di chiusura inaspettata della socket, restituire 0
     * - gestire eventuali interruzioni, riprendendo la ricezione da dove era
     *   stata interrotta
     * - gestire eventuali errori, terminando l'applicazione
     *
     */
    int ret;
    int recv_bytes = 0;
    do{
        ret = recv(sd, msg + recv_bytes, 1, 0);
        if(ret == -1 && errno == EINTR) continue;
        if(ret == -1) handle_error("errore recv");
        if(ret == 0) break;
    }while(msg[recv_bytes++] != '\0');
    
    printf("byte ricevuti: %d\n", recv_bytes);
    return recv_bytes;

}
