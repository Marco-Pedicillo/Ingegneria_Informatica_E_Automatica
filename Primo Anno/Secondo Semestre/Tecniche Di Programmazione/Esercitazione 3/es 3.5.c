#include <stdio.h>
#include <stdlib.h>

int main(){

    int n;

    printf("inserisci un intero n: ");
    scanf("%d",&n);
    
    int *p =(int*)malloc(sizeof(int));
    for (int i=0; i<n; i++)
        printf("posizione %d indirizzo= %p contenuto= %d\n", i,p+i,*(p+i));

    free(p);
    p= NULL;
}       