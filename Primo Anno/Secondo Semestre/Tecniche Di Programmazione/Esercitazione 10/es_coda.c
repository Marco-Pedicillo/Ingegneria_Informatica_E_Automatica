#include "coda.c"

void stampa_sequenza(void);
void printCoda(Coda *c);
int elemento_iesimo(Coda *c, int pos);
void avoid_stampa(Coda *c, int elem);
Coda * elementi_pari(Coda *c);

int main(){

    // 10.6
    printf("10.6\n");
    stampa_sequenza();
    printf("\n");

    // 10.7
    printf("10.7\n");
    Coda *c = codaVuota();
    inCoda(c,6);
    inCoda(c,5);
    inCoda(c,4);
    inCoda(c,3);
    inCoda(c,2);
    inCoda(c,1);
    T e = elemento_iesimo(c,2);
    printf("\n");
    printf("%d",e);
    printf("\n");
    printf("\n");

    // 10.8
    printf("10.8\n");
    Coda *C = codaVuota();
    inCoda(C,6);
    inCoda(C,5);
    inCoda(C,6);
    inCoda(C,6);
    inCoda(C,2);
    inCoda(C,1);
    avoid_stampa(C,6);
    printf("\n");

    // 10.10
    printf("10.10\n");
    Coda *coda = codaVuota();
    inCoda(coda,6);
    inCoda(coda,5);
    inCoda(coda,6);
    inCoda(coda,6);
    inCoda(coda,2);
    inCoda(coda,1);
    elementi_pari(coda);


}

void printCoda(Coda *c){
    while(!estCodaVuota(c)){
        printf("\n");
        printf("%d",primoCoda(c));
        outCoda(c);
    }
    printf("\n");
}

void stampa_sequenza(void){

    T e;
    Coda * c = codaVuota();
    printf("inserisci un numero:\n ");
    scanf("%d", &e);
    inCoda(c,e);
    while (e>0){
        printf("inserisci un numero:\n ");
        scanf("%d", &e);
        inCoda(c,e);
    }
    
    printCoda(c);

}

int elemento_iesimo(Coda *c, int pos){

    for (int i=0; i<pos; i++)
        outCoda(c);

    if (!estCodaVuota(c))
        return (primoCoda(c));
    else
        return (-1);

}

void avoid_stampa(Coda *c, int elem){

    Coda *c1 = codaVuota();
    Coda *c2 = codaVuota();
    Coda *c3 = codaVuota();

    while (!estCodaVuota(c)){
        inCoda(c1,primoCoda(c));
        inCoda(c2,primoCoda(c));
        
        outCoda(c);
    }
    while(!estCodaVuota(c1)){
        if (primoCoda(c1) != elem){
            inCoda(c3,primoCoda(c1));
            outCoda(c1);
        }    
        else
            outCoda(c1);
    }
    while (!estCodaVuota(c2)){
        inCoda(c,primoCoda(c2));
        outCoda(c2);
    }
    
    printCoda(c);
    printCoda(c3);

}

Coda * elementi_pari(Coda *c){

    Coda *c1 = codaVuota();
    while (!estCodaVuota(c)){
        inCoda(c1,primoCoda(c));
        outCoda(c);
        outCoda(c);
    }
    printCoda(c1);

}