#include <stdio.h>

int expected_f(int x, int y){
    int r = x * (y - 1) - 4;
    return y + r; 
}

int f(int x, int y);
int g(int x, int y, int z);

int main(){
    g(1, 2, 3); // non considerare g! L'errore e' altrove!
    int r = f(3, 7);
    printf("Valore: atteso=%d ottenuto=%d => %s\n", expected_f(3, 7), r, r == expected_f(3, 7) ? "OK" : "KO");
    printf("Risultato: %d/1\n", r == expected_f(3, 7));
    return 1;
}
