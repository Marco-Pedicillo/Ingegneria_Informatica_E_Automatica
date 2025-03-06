#include <stdio.h>

int n;
int primo=1;
int secondo=1;
int terzo;

int main() {

    printf("inserisci un numero n: ");
    scanf("%d", &n);

    printf("%d\n",primo);
    printf("%d\n", secondo);

    for (int i=2;i<n;i++){
        terzo=primo+secondo;
        primo=secondo;
        secondo=terzo;

        printf("%d\n",terzo);
    }


}