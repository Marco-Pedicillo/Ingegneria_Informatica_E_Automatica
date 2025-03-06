#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>

int main(){
    unsigned char b;
    short s;
    int i;
    long l;
    float f;
    double d;
    char c;

    printf("inserisci b: ");
    scanf("%c",&b);
    printf("inserisci s: ");
    scanf("%hd",&s);
    printf("inserisci i: ");
    scanf("%d",&i);
    printf("inserisci l: ");
    scanf("%ld",&l);
    printf("inserisci f: ");
    scanf("%f",&f);
    printf("inserisci d: ");
    scanf("%lf",&d);
    printf("inserisci c: ");
    scanf("%c",&c);

    printf("%d\n", b+10l);
    printf("%d\n",(b+i)*l);
    printf("%f\n",(b+i)*l+f);
    printf("%f\n",(s/f)+sin(f));
    if(c=='b')
        printf("true");
    else
        printf("false");
    
    printf("%f",l+1.5f);
    if(i<10)
        printf("true");
    else
        printf("false");
    
    printf("%d",d*3.14159);
    
}