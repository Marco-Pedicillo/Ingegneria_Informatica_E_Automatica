#include <stdio.h>

int main (int argc, char **argv){
    int n;
    printf("inserire il numero: ");
    scanf("%d", &n);

    if(n<1) {
        printf("deve essere positivo\n");
        return -1;
    }

    int i=1;
    for(int r=0; r<n; ++r){
        for(int c=0; c<=r; ++c)
            printf("%d\t",i++);

        printf("\n");    
    }
    return 0;
}        