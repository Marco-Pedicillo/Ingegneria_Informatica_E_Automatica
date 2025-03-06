#include <stdio.h>

int a,b,x;

int main() {
  
  printf("inserisci un intero a: ");
  scanf("%d", &a);
  printf("inserisci un intero b: ");
  scanf("%d", &b);

  x=-(b/a);
  printf("%d",x);

}