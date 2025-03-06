#include <stdio.h>

int main() {
    int n1;
    int n2;
    int n3;
    printf("inserisci un numero n: ");
    scanf("%d", &n1);
    printf("inserisci un numero n: ");
    scanf("%d", &n2);
    printf("inserisci un numero n: ");
    scanf("%d", &n3);

    if (n1>n2 && n2>n3)
        printf("%d",n3,n2,n1);
}