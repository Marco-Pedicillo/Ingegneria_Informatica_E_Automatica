#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main() {
    float num,minimo;
    printf("inserire un numero: ");
    scanf("%f",&num);

    minimo=num;

    while(num !=0.0){
        printf("inserire un numero: ");
        scanf("%f",&num);
        if(num<minimo && num!=0.0)
            minimo=num;
    }
    printf("il minimo è: %f\n", minimo);
    return 0;
}        
