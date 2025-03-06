#include "albero_Binario.c"
#include "lista.c"

TipoInfoAlbero trova_massimo(TipoAlbero a);
TipoInfoAlbero somma_foglie(TipoAlbero a);
int cerca_livello(TipoAlbero a, TipoInfoAlbero v);
int conta_dispari(TipoAlbero a);
int somma_singoli(TipoAlbero a);
TipoLista percorso_lungo(TipoAlbero a);
TipoAlbero scambia_foglie(TipoAlbero a);

int main(){
    TipoAlbero A = creaAlbBin (5, albBinVuoto(), albBinVuoto());
    TipoAlbero B = creaAlbBin (3, albBinVuoto(), albBinVuoto());
    TipoAlbero C = creaAlbBin (6, albBinVuoto(), albBinVuoto());
    TipoAlbero D = creaAlbBin (12, albBinVuoto(), albBinVuoto());
    TipoAlbero E = creaAlbBin (34, A , B);
    TipoAlbero F = creaAlbBin (65, C , D);
    TipoAlbero G = creaAlbBin (23, E , F);

    TipoAlbero a = creaAlbBin (5, albBinVuoto(), albBinVuoto());
    TipoAlbero d = creaAlbBin (12, albBinVuoto(), albBinVuoto());
    TipoAlbero e = creaAlbBin (34, a , albBinVuoto());
    TipoAlbero f = creaAlbBin (65, albBinVuoto() , d);
    TipoAlbero g = creaAlbBin (23, e , f);



    stampaParentetica(G);
    printf("\n\n");

    // 11.1
    printf("(11.1)");
    TipoInfoAlbero massimo = trova_massimo(G);
    printf(" %d", massimo);
    printf("\n");

    // 11.2
    printf("(11.2)");
    TipoInfoAlbero somma_Foglie = somma_foglie(G);
    printf(" %d", somma_Foglie);
    printf("\n");

    // 11.3
    printf("(11.3)");
    TipoInfoAlbero liv_valore = cerca_livello(G,12);
    printf(" %d",liv_valore);
    printf("\n");

    // 11.4
    printf("(11.4)");
    TipoInfoAlbero disp = conta_dispari(G);
    printf(" %d", disp);
    printf("\n");

    // 11.5
    printf("(11.5)");
    TipoInfoAlbero somma_Singoli = somma_singoli(g);
    printf(" %d", somma_Singoli);
    printf("\n");

    // 11.7
    printf("(11.7)");
    TipoLista l = percorso_lungo(G);
    printlist(l);

    // 11.9
    printf("(11.9)");
    TipoAlbero alb = scambia_foglie(G);
    stampaParentetica(alb);



}

TipoInfoAlbero max(int a, int b){
  if (a>=b) return a;
  else return b;
}

bool estFoglia(TipoAlbero a){
    return (estVuoto(sinistro(a)) && estVuoto(destro(a)));
}

int len_list (TipoLista l){
    if (estVuota(l))
        return 0;
    else 
        return 1 + len_list(cdr(l));
}

TipoInfoAlbero trova_massimo(TipoAlbero a){
    if (estVuoto(a)) 
        return -1;
    else if (estFoglia(a)) 
        return radice(a);
    else{
        int m1 = max(trova_massimo(destro(a)), trova_massimo(sinistro(a)));
        TipoInfoAlbero info = radice(a);
        return max(info, m1);
    }
}

TipoInfoAlbero somma_foglie(TipoAlbero a){
    if (estVuoto(a))
        return 0;
    if (estFoglia(a))
        return radice(a);
    else
        return somma_foglie(sinistro(a)) + somma_foglie(destro(a));     
}

int cerca_livello_aux(TipoAlbero a, TipoInfoAlbero v, int liv){
    if (estVuoto(a))
        return -1;
    else if (radice(a) == v)
        return liv;
    else{
        int sx = cerca_livello_aux(sinistro(a),v,liv+1);
        int dx = cerca_livello_aux(destro(a),v,liv+1);
        if (sx != -1)
            return sx;
        else   
            return dx;
    } 
}

int cerca_livello(TipoAlbero a, TipoInfoAlbero v){
    return cerca_livello_aux(a,v,0);
}

int conta_dispari(TipoAlbero a){
    if (estVuoto(a))
        return 0;
    else {
        int sum = radice(a);
        if (!estVuoto(sinistro(a)))
            sum += radice(sinistro(a));
        if (!estVuoto(destro(a)))
            sum += radice(destro(a));
        if (sum % 2 != 0)
            return 1 + conta_dispari(sinistro(a)) + conta_dispari(destro(a));
        else
            return conta_dispari(sinistro(a)) + conta_dispari(destro(a));                                           
    }
}

int somma_singoli(TipoAlbero a){
    if (estVuoto(a))
        return 0;
    else if (estFoglia(a))
        return 0;
    else if ((estVuoto(sinistro(a)) && !estVuoto(destro(a))) 
            || (!estVuoto(sinistro(a)) && estVuoto(destro(a))))
        return radice(a);  
    else   
        return somma_singoli(sinistro(a)) + somma_singoli(destro(a)); 
}

TipoLista percorso_lungo(TipoAlbero a){
    if (estVuoto(a))
        return listaVuota();
    else if (estFoglia(a))
        return cons(radice(a),percorso_lungo(sinistro(a)));
    else if (!estVuoto(sinistro(a)) && estVuoto(destro(a)))
        return cons(radice(a),percorso_lungo(sinistro(a)));
    else if (estVuoto(sinistro(a)) && !estVuoto(destro(a)))
        return cons(radice(a), percorso_lungo(destro(a)));
    else {
        TipoLista sx = cons(radice(a), percorso_lungo(sinistro(a)));
        TipoLista dx = cons(radice(a), percorso_lungo(destro(a)));
        if (len_list(sx) > len_list(dx))
            return sx;
        else
            return dx;
    }    
}

TipoAlbero scambia_foglie(TipoAlbero a){
    if (estVuoto(a))
        return albBinVuoto();
    else if (estFoglia(sinistro(a)) && estFoglia(destro(a)))
        return creaAlbBin(radice(a), destro(a), sinistro(a));
    else if (!estVuoto(sinistro(a)) && estVuoto(destro(a)))
        return creaAlbBin(radice(a), scambia_foglie(sinistro(a)), albBinVuoto());
    else if (!estVuoto(destro(a)) && estVuoto(sinistro(a)))
        return creaAlbBin(radice(a), albBinVuoto(), scambia_foglie(destro(a)));
    else    
        return creaAlbBin(radice(a), scambia_foglie(sinistro(a)), scambia_foglie(destro(a)));    
}