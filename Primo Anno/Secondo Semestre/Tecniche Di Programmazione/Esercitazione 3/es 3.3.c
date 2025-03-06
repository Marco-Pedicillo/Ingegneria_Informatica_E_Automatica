#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
  float *num = (float *)malloc(sizeof(float)); 
  printf("Inserire la temperatura: ");
  scanf("%f", num);

  char *scala = (char *)malloc(sizeof(char)); 
  printf("Inserire la scala (K, C, F): ");
  scanf("%c ", scala);

  switch(*scala) {
  case 'K':
    printf("C: %f\n", *num - 273.15f);
    printf("F: %f\n", (*num - 273.15f) * 9.0f / 5.0f + 32.0f);
    break;
  case 'C':
    printf("K: %f\n", *num + 273.15f);
    printf("F: %f\n", *num * 9.0f / 5.0f + 32.0f);
    break;
  case 'F':
    printf("K: %f\n", ((*num - 32.0f) * 5.0f / 9.0f) + 273.15f);
    printf("C: %f\n", (*num - 32.0f) * 5.0f / 9.0f);
    break;
  default:
    break;
  }

  free(scala);
	scala = NULL;
  free(num);
	num = NULL;

  return 0;
}
