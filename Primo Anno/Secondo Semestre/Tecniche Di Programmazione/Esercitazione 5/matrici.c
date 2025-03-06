#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include <matricih.h>

Mat* mat_alloc(int rows, int cols);
Mat* Mat_read(const char *filename);
void mat_free(Mat *m);
void mat_print(Mat *m);
Mat * mat_clone(Mat *m);

int main(){
    
    //5.1
    printf("leggo il file mat_1.txt");
    Mat *m1= Mat_read("mat_1.txt");
    printf("\n\n");

    //5.2
    mat_free(m1);
    printf("\n\n");

    //5.3
    printf("m1:\n");
    mat_print(m1);
    printf("\n");

    //5.4
    Mat *copy_m1= mat_clone(m1);
    mat_print(copy_m1);
    printf("\n\n");

}

Mat* mat_alloc(int rows, int cols){
    Mat* m= (Mat*)malloc(sizeof(Mat));
    m -> rows= rows;
    m -> cols= cols;
    m -> rows_pt= (float**)malloc(rows*sizeof(float*));
    for (int i=0; i< m->rows; i++)
        m ->rows_pt[i]= (float*)malloc(m->cols * sizeof(float));
    
    return m;
}

Mat* Mat_read(const char *filename){
    FILE *fp= fopen(filename, "r");
    if (fp== NULL){
        printf("Errore nell'apertura del file %s\n", filename);
        fclose(fp);
        return NULL;
    }

    int rows= 0;
    if (fscanf(fp,"%d",&rows) != 1){
        printf("Non riesco a leggere il numero di righe nel file %s\n",filename);
        fclose(fp);
        return NULL;
    }
    if (rows == 0)
        return NULL;
    
    int cols= 0;
    if (fscanf(fp, "%d", &cols) != 1){
        printf("Non riesco a leggere il numero di colonne nel file %s\n",filename);
        fclose(fp);
        return NULL;
    }
    if(cols == 0)
        return NULL;
    
    Mat *m= mat_alloc(rows,cols);
    for(int r=0; r<rows; r++){
        for(int c=0; c<cols; c++){
            float valore= 0.0f;
            if (fscnaf(fp, "%f", &valore) != 1){
                printf("Non riesco a leggere tutti gli elementi del file %s\n",filename);
                fclose(fp);
                return NULL;
            }
            m ->rows_pt[r][c]= valore;
        }
    }
    fclose(fp);
    return m;
}   

void mat_free(Mat *m){
    for (int i=0; i< m->rows; i++)
        free(m -> rows_pt[i]);
    free(m-> rows_pt);
    free(m);
}

void mat_print(Mat *m){
    for (int i=0; i< m->rows; i++){
        for (int j=0; j< m->cols; j++)
            printf("%lf", m-> rows_pt[i][j]);
        printf("\n");
    }
}

Mat * mat_clone(Mat *m){
    Mat *copy= Mat_alloc(m->rows, m->cols);

    for(int i=0; i< m->rows; i++){
        for(int j=0; j< m->cols; j++)
            copy -> rows_pt[i][j]= m->rows_pt[i][j];
    }
    return copy;
}