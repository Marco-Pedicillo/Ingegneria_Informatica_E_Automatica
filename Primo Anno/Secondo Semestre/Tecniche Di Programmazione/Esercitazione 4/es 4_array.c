#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//dichiarazioni
void print_array(int array[], int len);
void random_array(int v[], int dim, int max_value);
double* vec_clone(const double v[], int dim);
int * numeri_unici(const int array[], int dim, int *output_dim);


int main(){

    //4.1
    int dim = 30;
    int v[dim];
    int max_value = 8;
    random_array(v,dim,max_value);
    print_array(v,dim);
    puts("");

    //4.2
    int dim_double= 4;
    double v2[]= {0.0, 2.0, -0.5, +2.0};
    double *v2_copia= vec_clone(v2,dim_double);

    printf("%lf\n", v2_copia);

    //4.4
    int unici_len;
    int *unici= numeri_unici(v,dim,&unici_len);
    print_array(unici,unici_len);
    

}

void print_array(int array[], int dim) {

	putchar('[');
	for (int i = 0; i < dim; ++i) {
		const char *format = (i < dim - 1)? "%d, ": "%d";
		printf(format, array[i]);
	}
	puts("]");
}

void random_array(int v[], int dim, int max_value){
    for (int i=0; i<dim; i++)
        v[i]= rand() % max_value;
}

double* vec_clone(const double v[], int dim){
    double* copia= (double*)malloc(dim*sizeof(double));
    for (int i=0; i<dim; i++)
        copia[i]= v[i];
    
    return copia;
}

int * numeri_unici(const int array[], int dim, int *output_dim){
    int *unici= (int*)malloc(dim*sizeof(int));
    int array_i= 0, unici_i= 0;

    while(array_i<dim){
        int corrente= array[array_i];

        bool trovato= false;
        for (int j=0; j<unici_i; j++){
            if (unici[j] == corrente){
                trovato = true;
                break;
            }
        }

        if (!trovato)
            unici[unici_i++] = corrente;
        
        array_i++;
    }

    *output_dim= unici_i;
    unici= (int*)realloc(unici,unici_i);

    return unici;
}



