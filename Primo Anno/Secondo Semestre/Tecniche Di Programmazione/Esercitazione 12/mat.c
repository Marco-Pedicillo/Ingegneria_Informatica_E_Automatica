#include <stdio.h>
#include <stdlib.h>
#include "mat.h"

Mat* mat_alloc(int rows, int cols){
    Mat* m= (Mat*)malloc(sizeof(Mat));
    m -> rows= rows;
    m -> cols= cols;
    m -> rows_pt= (float**)malloc(rows*sizeof(float*));
    for (int i=0; i< m->rows; i++)
        m ->rows_pt[i]= (float*)malloc(m->cols * sizeof(float));
    
    return m;
}

void mat_print(Mat *m){
    for (int i=0; i< m->rows; i++){
        for (int j=0; j< m->cols; j++)
            printf("%lf", m-> rows_pt[i][j]);
        printf("\n");
    }
}

void mat_free(Mat *m){
    for (int i=0; i< m->rows; i++)
        free(m -> rows_pt[i]);
    free(m-> rows_pt);
    free(m);
}