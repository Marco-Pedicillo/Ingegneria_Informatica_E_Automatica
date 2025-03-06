#include <stdio.h>
#include <stdlib.h>

int main() {
    int a= sizeof(int);
    int b=sizeof(float);
    int c=sizeof(double);
    int d=sizeof(char);
    int e=sizeof(short int);
    int f=sizeof(long int);
    
    printf("%d\n%d\n%d\n%d\n%d\n%d\n",a,b,c,d,e,f);
}    

