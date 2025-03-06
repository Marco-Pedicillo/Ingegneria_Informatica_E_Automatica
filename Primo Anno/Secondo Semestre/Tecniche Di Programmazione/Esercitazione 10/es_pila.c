#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.c"

void printPila(Pila *p);
void stampa_sequenza_inversa(void);
void rimuovi_alcuni(Pila *p, const int *rimuovere, int n);
bool check_palindrome(const char* s);

int main(){

    // 10.1
    stampa_sequenza_inversa();

    // 10.2
    const int rimuovere[]={2,1,3};
    int n = 3;
    Pila *p = pilaVuota();
    inPila(p,5);
    inPila(p,4);
    inPila(p,3);
    inPila(p,2);
    inPila(p,1);
    rimuovi_alcuni(p,rimuovere,n);
    printPila(p);

    // 10.3
    const char *s = "abba";
    const char *s1 = "";
    const char *s2 = "acca";
    bool ris = check_palindrome(s);
    bool ris1 = check_palindrome(s1);
    bool ris2 = check_palindrome(s2);
    if (ris == true)
        printf("True\n");
    else
        printf("False\n"); 

    if (ris1 == true)
        printf("True\n");
    else
        printf("False\n"); 

    if (ris2 == true)
        printf("True\n");
    else
        printf("False\n");     

}

void printPila(Pila *p){
    while(!estPilaVuota(p)){
        printf("\n");
        printf("%d",primoPila(p));
        outPila(p);
    }
    printf("\n");
}

void stampa_sequenza_inversa(void){
    
    T e;
    Pila *p = pilaVuota();

    printf("inserisci un numero: \n");
    scanf("%d", &e);
    inPila(p,e);
    while (e>0){
        printf("inserisci un numero: \n");
        scanf("%d", &e);
        inPila(p,e);
    }
    outPila(p);   
    printPila(p);

}

void rimuovi_alcuni(Pila *p, const int *rimuovere, int n){

    bool cond = 0;
    for (int i=0; i<n; i++){
        if(cond==0){
            if(rimuovere[i] == primoPila(p))
                cond = 1;
        }
    }
    if (cond == 1){
        outPila(p);
        rimuovi_alcuni(p,rimuovere,n);
    }
    else
        return;
}

bool check_palindrome(const char* s){

    Pila *p = pilaVuota();
    Pila *normale = pilaVuota();
    Pila *inversa = pilaVuota();

    if (s == "")
        return true; 
    for (int i=0; i<strlen(s); i++){
        inPila(p,s[i]);
        inPila(normale,s[i]);
    }    
    while(!estPilaVuota(p)){
        inPila(inversa,primoPila(p));
        outPila(p);
    }
    while (!estPilaVuota(normale)){
        if (primoPila(normale) == primoPila(inversa)){
           outPila(normale);
           outPila(inversa);
        }
        else
            return false;
    }
    return true;
}

