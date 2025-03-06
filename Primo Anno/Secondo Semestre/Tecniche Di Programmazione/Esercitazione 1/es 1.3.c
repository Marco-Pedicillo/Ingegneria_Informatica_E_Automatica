#include <stdio.h>

int n,i,j;
char a='*';

int main() {
    printf("inserisci un numero n: ");
    scanf("%d", &n);

    for (i=0;i<n;i++){
        for (j=0;j<n;j++){
            printf("%c",a);
        }
        printf("\n");
    }
        
}