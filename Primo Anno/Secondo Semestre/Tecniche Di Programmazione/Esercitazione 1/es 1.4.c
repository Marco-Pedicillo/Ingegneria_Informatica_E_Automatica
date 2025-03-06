#include <stdio.h>

int n,j,i;

int main() {
    for (j=1;j<=n;j++)
        printf("*");
    printf("\n");
    

    for (i=2;i<=n-1;i++){
        printf("*");
        for (j=2;j<=n-1;j++)
            printf(" ");
        printf("*");
        printf("\n");
        
    }

    for (j=1;j<=n;j++)
        printf("*");
    printf("\n");
    
}