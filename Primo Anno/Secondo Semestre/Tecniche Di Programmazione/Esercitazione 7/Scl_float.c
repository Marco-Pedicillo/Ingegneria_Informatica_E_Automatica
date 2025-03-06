#include <stdio.h>
#include <stdlib.h>

//SCL FLOAT
typedef float TipoInfoSCL;
struct ElemSCL {
TipoInfoSCL info;
struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;

//FUNZIONI
int emptySCL(TipoSCL scl);
void addSCL(TipoSCL *scl, TipoInfoSCL e);
void writeSCL(TipoSCL scl);
int scl_len(TipoSCL scl);
float scl_sum(TipoSCL scl);
float scl_media(TipoSCL scl);
float scl_dot(TipoSCL scl1, TipoSCL scl2);
void scl_duplicate_pos(TipoSCL scl, int pos); 
TipoSCL scl_positives(TipoSCL scl);


int main(){
    TipoSCL scl1 = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl1 = NULL;
    addSCL(&scl1,3.0);
    addSCL(&scl1,2.0);
    addSCL(&scl1,1.0);

    TipoSCL scl2 = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl2 = NULL;
    addSCL(&scl2,6.0);
    addSCL(&scl2,5.0);
    addSCL(&scl2,4.0);
    
    TipoSCL scl = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl = NULL;

    TipoSCL scl3 = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl3 = NULL;
    addSCL(&scl3,0.0);
    addSCL(&scl3,5.0);
    addSCL(&scl3,4.0);
    addSCL(&scl3,-4.0);
    addSCL(&scl3,-8.0);

    //7.1
    int len = scl_len(scl1);
    printf("lunghezza: %d", len);
    printf("\n");

    //7.2
    int somma = scl_sum(scl1);
    printf("somma: %d", somma);
    printf("\n");

    //7.3
    int media = scl_media(scl1);
    printf("media: %d", media);
    printf("\n");

    //7.4
    int dot = scl_dot(scl1,scl2);
    printf("dot: %d", dot);
    printf("\n");

    //7.5
    scl_duplicate_pos(scl1, 1);
    writeSCL(scl1);
    printf("\n");

    //7.6
    scl_positives(scl3);
    writeSCL(scl3);
    printf("\n");

}

int emptySCL(TipoSCL scl){
    return scl== NULL;
}

void addSCL(TipoSCL *scl, TipoInfoSCL e){
    TipoSCL temp = *scl;
    *scl = (TipoNodoSCL*)malloc(sizeof(TipoInfoSCL));
    (*scl) -> info = e;
    (*scl) -> next = temp;
}

void writeSCL(TipoSCL scl){
    if (emptySCL(scl))
        printf("\n");
    else{
        printf("%f\n", scl->info);
        writeSCL(scl->next);
    }
}

int scl_len(TipoSCL scl){
    if (emptySCL(scl))
        return 0;
    else
        return 1+scl_len(scl -> next);
}

float scl_sum(TipoSCL scl){
    if (emptySCL(scl))
        return 0;
    else
        return ((scl) -> info) + scl_sum(scl -> next);
}

float scl_media(TipoSCL scl){
    if (emptySCL(scl))
        return 0;
    else{
        float sum = scl_sum(scl);
        float len = scl_len(scl);
        return (sum/len);
    }
}

float scl_dot(TipoSCL scl1, TipoSCL scl2){
    if (emptySCL(scl1) || emptySCL(scl2))
        return 0;
    else
        return (scl1->info)*(scl2->info) + scl_dot(scl1->next,scl2->next);
}

void scl_duplicate_pos(TipoSCL scl, int pos){
    
    if (pos==0){
        TipoSCL temp;
        temp = (TipoNodoSCL*)malloc(sizeof(TipoNodoSCL));
        temp->info = scl->info;
        temp->next = scl->next;
        scl->next = temp;
        return;
    }
    else {
        pos--;
        return scl_duplicate_pos(scl->next,pos);
    }
}

TipoSCL scl_positives(TipoSCL scl){

    if (emptySCL(scl))
        return 0;
    else if (scl->info >= 0){
        TipoSCL new = (TipoSCL)malloc(sizeof(TipoNodoSCL));
        new -> info = scl -> info;
        new -> next = scl_positives(scl -> next);
        return new;
    }
    else
        scl_positives(scl -> next);
}