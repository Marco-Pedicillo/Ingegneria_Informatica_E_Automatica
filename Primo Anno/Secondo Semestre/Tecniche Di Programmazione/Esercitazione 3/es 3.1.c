#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int *num = (int*)malloc(sizeof(int));
    int *minimo = (int*)malloc(sizeof(int));


    while (1){
        printf("inserisci un numero positivo, 0 per terminare: ");
        scanf("%d",num);

        if (*num == 0){
            break;
        }
            
        if (*num < 0){
            printf("Errore\n");
            return 1;
        }

        if (*num < *minimo || *minimo == 0)
            *minimo = *num;
    }

    printf("il numero minimo è: %d\n",*minimo);

    free(minimo);
    free(num);
}