#include "col2row.h"

static int sum(int** a, int n, int j) {
    int i, s;
    for (i=s=0; i<n; ++i) s += a[i][j];
    return s;
}

void col2row(int** a, int n, int i, int j) {
    int k;
    int somma = sum(a, n, j);
    for (k=0; k<n; ++k)
	if(k<=j) a[i][k] += somma;
	else a[i][k] += 2*somma; 
}
