#include <stdlib.h>
#include <math.h> 
int main() {
    int M;
    printf("inserisci M: "); 
    scanf("%d", &M);

    if(M<1){
        printf("Il blocco deve avere dimensione strettamente positiva!\n");
        return -1;
    }


    int N;
    printf("")    