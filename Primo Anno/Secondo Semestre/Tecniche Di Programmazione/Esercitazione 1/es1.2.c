#include <stdio.h>

int main() {

    float num;
    float den;
    
    float n;
    while (n!=0) {
        printf("inserisci n: ");
        scanf("%f",&n);

        den++;
        num+=n;

    }
    den--;

    float ris=(num/den);
    printf("%f",ris);

}