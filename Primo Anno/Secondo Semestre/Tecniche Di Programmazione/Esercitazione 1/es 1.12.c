#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main (int argc, char **argv){
    int n1;
    printf("inserire un intero: \n");
    scanf("%d", &n1);

    int n2;
    printf("inserire un intero: \n");
    scanf("%d", &n2);

    long prodotto= n1*n2;
    long mcm= (n1>n2)? n1: n2;
    
    for (;mcm<= prodotto; mcm++)
    {
        if (mcm%n1==0 && mcm%2==0)
        break;
    }

    printf("mcm: %ld\n",mcm);
    return 0;
}