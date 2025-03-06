#include "lista.c"
#include "albero_binario.c"
#include "mat.c"
#include "scl.h"

int singleChildSum(TipoAlbero a);
int livelli_completi(TipoAlbero a);
TipoLista listaNodiFoglia(TipoAlbero a);
int conditionalSum(Mat* src, int flag);
TipoAlbero taglia_livello(TipoAlbero a, int livello);
int contieneElemento(TipoSCL scl, TipoInfoSCL e);
TipoSCL complemento(TipoSCL scl, TipoSCL elementiDaScartare);
int next_step(Mat *mat, char direction);
TipoLista inFondo(TipoLista l);
TipoLista invertiInParte(TipoLista l, int inizio);

// AUX
bool estFoglia (TipoAlbero a){
    return (estVuoto(sinistro(a)) && estVuoto(destro(a)));
}

TipoLista listaNodiFoglia_Aux(TipoAlbero a, TipoLista l){
    if (estVuoto(a))
        return l;
    else if (estFoglia(a))  
        l = cons(radice(a), l);
    l =  listaNodiFoglia_Aux(sinistro(a), l);
    l =  listaNodiFoglia_Aux(destro(a), l);
    return l;
}

int emptySCL (TipoSCL scl){
    return scl == NULL;
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
        printf("%d\n", scl->info);
        writeSCL(scl->next);
    }
}

TipoLista append (TipoLista l , T e){
    if (estVuota(l))
        return cons (e,l);
    return cons(car(l),append(cdr(l),e));
}

int somma_sottoalbero(TipoAlbero a){
    if (estVuoto(a))
        return 0;
    else 
        return radice(a) + somma_sottoalbero(sinistro(a)) + somma_sottoalbero(destro(a));
}

void snake_pos(Mat *mat, int *x, int *y){
    for (int i = 0; i < mat->rows; i++){
        for (int j = 0; j < mat-> cols; j++){
            if (mat ->rows_pt[i][j] == 'X'){
                *x = i;
                *y = j;
                return;
            }
        }
    }
}

int main(){
    TipoAlbero a = creaAlbBin (5, albBinVuoto(), albBinVuoto());
    TipoAlbero b = creaAlbBin (12, albBinVuoto(), albBinVuoto());
    TipoAlbero c = creaAlbBin (65, a , albBinVuoto());
    TipoAlbero d = creaAlbBin (20, albBinVuoto() , b);
    TipoAlbero e = creaAlbBin (23, d , c);

    Mat *mat1 = mat_alloc(3,3);
    int x = 1;
    for (int i = 0; i<=2; i++){
        for (int j = 0; j <=2; j++){
            mat1 -> rows_pt[i][j] = x;
            x++;
        }
    }

    Mat *mat2 = mat_alloc(4,4);
    mat2 ->rows_pt[0][0] = '#';
    mat2 ->rows_pt[0][1] = '#';
    mat2 ->rows_pt[0][2] = '#';
    mat2 ->rows_pt[0][3] = '#';
    mat2 ->rows_pt[1][0] = '#';
    mat2 ->rows_pt[1][1] = 'X';
    mat2 ->rows_pt[1][2] = 'o';
    mat2 ->rows_pt[1][3] = '#';
    mat2 ->rows_pt[2][0] = '#';
    mat2 ->rows_pt[2][1] = ' ';
    mat2 ->rows_pt[2][2] = ' ';
    mat2 ->rows_pt[2][3] = '#';
    mat2 ->rows_pt[3][0] = '#';
    mat2 ->rows_pt[3][1] = '#';
    mat2 ->rows_pt[3][2] = '#';
    mat2 ->rows_pt[3][3] = '#';


    TipoSCL scl = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl = NULL;
    addSCL(&scl, 6);
    addSCL(&scl, 5);
    addSCL(&scl, 4);
    addSCL(&scl, 3);
    addSCL(&scl, 2);
    addSCL(&scl, 0);

    TipoSCL scl1 = (TipoSCL) malloc (sizeof(TipoNodoSCL));
    scl1 = NULL;
    addSCL(&scl1, 5);
    addSCL(&scl1, 3);


    TipoLista lista = cons(5,cons(4,cons(3,cons(2,cons(1,cons(0,listaVuota()))))));
    
    

    // 12.1
    printf("(12.1) ");
    TipoInfoAlbero sum = singleChildSum(e);
    printf("%d", sum);
    printf("\n");

    // 12.2
    printf("(12.2) ");
    TipoInfoAlbero liv = livelli_completi(e);
    printf("%d", liv);
    printf("\n");

    // 12.3
    printf("(12.3) ");
    TipoLista list = listaNodiFoglia(e);
    printlist(list);

    // 12.4
    printf("(12.4) ");
    mat_print(mat1);
    int sum_m0 = conditionalSum(mat1, 0);
    int sum_m1 = conditionalSum(mat1, 1);
    printf("%d, %d", sum_m0, sum_m1);
    printf("\n");

    // 12.5
    printf("(12.5) ");
    TipoAlbero alb = taglia_livello(e, 2);
    stampaParentetica(alb);
    printf("\n");
    
    // 12.6
    printf("(12.6) ");
    int ris = contieneElemento(scl, 3);
    int ris1 = contieneElemento(scl, 8);
    printf("%d %d", ris, ris1);
    printf("\n");

    // 12.7
    printf("(12.7) ");
    TipoSCL nuova = complemento(scl, scl1);
    writeSCL(nuova);

    // 12.8
    printf("(12.8) ");
    int ris_snake = next_step(mat2, d);
    printf("%d", ris_snake);
    printf("\n");

    // 12.9
    printf("(12.9) ");
    TipoLista l = inFondo(lista);
    printlist(l);

    // 12.10
    printf("(12.10) ");
    TipoLista l1 = invertiInParte(lista, 3);
    printlist(l1);

}

int singleChildSum(TipoAlbero a){
    if (estVuoto(a))
        return 0;
    else if (estFoglia(a))
        return 0;
    else if ((estVuoto(sinistro(a)) && !estVuoto(destro(a)))
            || (!estVuoto(sinistro(a)) && estVuoto(destro(a))))
        return radice(a);
    else    
        return singleChildSum(sinistro(a)) + singleChildSum(destro(a));
}

int livelli_completi(TipoAlbero a){
    if (estVuoto(a))
        return -1;
    else if (!estVuoto(sinistro(a)) && !estVuoto(destro(a))){
        int l = 1 + livelli_completi(sinistro(a));
        int r = 1 + livelli_completi(destro(a));
        return l<r ? l:r; 
    }
}

TipoLista listaNodiFoglia(TipoAlbero a){
    return listaNodiFoglia_Aux(a, listaVuota());
}

int conditionalSum(Mat* src, int flag){
     int sum = 0;
     for (int i = 0; i < src -> rows; i++){
        for (int j = 0; j < src -> cols; j++){
            int sum1 = src -> rows_pt[i][j];
            if ((flag == 0 && j%2 != 0) || (flag == 1 && i%2 != 0))
                sum1 *= -1;
            sum += sum1;
        }
     }
     return sum;
}

TipoAlbero taglia_livello(TipoAlbero a, int livello){
    if (estVuoto(a))
        return albBinVuoto();
    else if (livello == 0)
        return creaAlbBin(somma_sottoalbero(a), albBinVuoto(), albBinVuoto());
    else
        return creaAlbBin(radice(a), taglia_livello(sinistro(a), livello-1), taglia_livello(destro(a), livello-1));        
}

int contieneElemento(TipoSCL scl, TipoInfoSCL e){
    if (emptySCL(scl))
        return 0;
    else if (scl -> info == e)
        return 1;
    else
        return contieneElemento(scl -> next, e);
}

TipoSCL complemento(TipoSCL scl, TipoSCL elementiDaScartare){
    if (scl == NULL)
        return NULL;
    else{ 
        if (!contieneElemento(elementiDaScartare, scl -> info)){
        TipoSCL slc_nuova = (TipoSCL) malloc (sizeof(TipoNodoSCL));
        slc_nuova -> info = scl -> info;
        slc_nuova -> next = complemento(scl -> next, elementiDaScartare);
        return slc_nuova;
        }
        else
            return complemento(scl->next, elementiDaScartare);
    }
}

int next_step(Mat *mat, char direction){
   int curr_x, curr_y;
    snake_pos(mat, &curr_x, &curr_y);
    int next_x, next_y;
    mat->rows_pt[curr_x][curr_y] = ' ';
    if(direction == 'w'){
        next_x = curr_x - 1;
        next_y = curr_y;
    }
    else if(direction == 'a'){
        next_x = curr_x;
        next_y = curr_y - 1;
    }
    else if(direction == 's'){
        next_x = curr_x + 1;
        next_y = curr_y;

    }
    else if(direction == 'd'){
        next_x = curr_x;
        next_y = curr_y + 1;
    }
    char next_pos = mat->rows_pt[next_x][next_y];
    if (next_pos == '#'){
        mat->rows_pt[next_x][next_y] = 'X';
        return -1;
    }
    else if (next_pos== 'o'){
        mat->rows_pt[next_x][next_y] = 'X';
        return 1;
    }
    else{
        mat->rows_pt[next_x][next_y] = 'X';
        return 0;
    }
}

TipoLista inFondo(TipoLista l){
    if (estVuota(l))
        return l;
    return append(cdr(l),car(l));
}

TipoLista invertiInParte(TipoLista l, int inizio){
    if (estVuota(l))
        return l;
    if (inizio > 0)
        return cons(car(l),invertiInParte(cdr(l), inizio-1));
    if (inizio == 0){
        int e = car(l);
        return append(invertiInParte(cdr(l), inizio), e);
    }
}