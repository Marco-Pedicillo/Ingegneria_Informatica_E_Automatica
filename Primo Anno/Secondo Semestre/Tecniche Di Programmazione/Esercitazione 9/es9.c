#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "lista.c"
#include <stdbool.h>
 
// FUNZIONI
int length ( TipoLista l );
TipoLista append (TipoLista l, T e);
TipoLista init(T *vec, int len);
TipoLista doubledCopy(TipoLista list);
TipoLista multipleSublist( TipoLista list, unsigned int m );
TipoLista subList(TipoLista list, int start, int end);
TipoLista interleave(TipoLista l1, TipoLista l2);

int main(){
    

    // 9.1
    printf("(9.1)\n");
    int v[4]={5,3,8,6};
    int len_v = 4;

    for (int i=0; i<len_v; i++)
        printf("%d ", v[i]);
    
    printf("\n");

    TipoLista l = init(v,len_v);
    
    printlist(l); 

    // 9.2
    printf("(9.2)\n");
     TipoLista list = doubledCopy(l);
     printlist(list);

    //  9.3
    printf("(9.3)\n");
    TipoLista list1 = multipleSublist(l,2);
    printlist(list1);

    // 9.4
    printf("(9.4)\n");
    TipoLista lista = subList(l,1,3);
    printlist(lista);

    // 9.5
    printf("(9.5)\n");
    int v2[]={0,9,8,7};
    int len_v2 = 4;
    TipoLista l2 = init(v2,len_v2);
    printlist(l);
    printlist(l2);

    TipoLista L = interleave(l,l2);
    printlist(L);

    // Bonus
    TipoLista LISTA = cons(1,cons(2,cons(3,cons(4, listaVuota()))));
    LISTA = append_(LISTA,7);
    printlist(LISTA);

}

int length(TipoLista l){
    if (estVuota(l)) 
        return 0;
    return 1 + length(cdr(l));
}

TipoLista init(T *vec, int len){

    TipoLista l= listaVuota();
    for (int i=len-1; i>=0; i--)
        l = cons(vec[i],l);
    
    return l;
}

TipoLista append (TipoLista l, T e){
    if (estVuota(l))
        return cons(e, l);
    
    return cons(car(l), append(cdr(l), e));
}

TipoLista doubledCopy(TipoLista list){

    TipoLista l = listaVuota();

    while (!estVuota(list)){
        T e = car(list);
        l = append(l,e);
        l = append(l,e);
        list = cdr(list);
    }
     return l;
    
}

TipoLista multipleSublist(TipoLista list, unsigned int m){

    if (estVuota(list))
        return listaVuota();
    else if (car(list) % m == 0)
        return cons(car(list),multipleSublist(cdr(list),m));
        else
            return multipleSublist(cdr(list),m);       
}

TipoLista subList(TipoLista list, int start, int end){

     if (estVuota(list) || end == 0) 
        return listaVuota();
    else if (start == 0) 
        return cons(car(list), subList(cdr(list), start, --end));
        else 
            return subList(cdr(list), --start, --end);
}

TipoLista interleave(TipoLista l1, TipoLista l2){
    if (estVuota(l1))
        return listaVuota();
    else
        return cons(car(l1),interleave(l2,cdr(l1)));
}

TipoLista append_(TipoLista list, T elem){
    if (!estVuota(list) && elem >= 5)
        return cons(elem,list);
    else if (car(list) >= 5)
        return cons(car(list), append_(cdr(list), elem));
    else
        return list;
}