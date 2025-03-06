#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// SCL CHAR
typedef char TipoInfoSCL;
struct ElemSCL {
TipoInfoSCL info;
struct ElemSCL *next;
};

typedef struct ElemSCL TipoNodoSCL;
typedef TipoNodoSCL * TipoSCL;

// FUNZIONI
int emptySCL(TipoSCL scl);
void addSCL(TipoSCL *scl, TipoInfoSCL e);
void writeSCL(TipoSCL scl);
void sclstring_print(TipoSCL s);
TipoSCL sclstring_create(const char *s);
bool sclstring_equals(TipoSCL scl, const char *s);
void sclstring_remove(TipoSCL *scl_p, char val);

int main(){
    TipoSCL scl_vuota = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl_vuota = NULL;

    TipoSCL scl = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl = NULL;
    addSCL(&scl,'c');
    addSCL(&scl,'b');
    addSCL(&scl,'a');

     char s[6] = "Ciao!";

     char val = 'a';

    // 7.7
    sclstring_print(scl);
    sclstring_print(scl_vuota);
    printf("\n");

    // 7.8
    sclstring_create(s);
    printf("\n");

    // 7.9
    bool ris = sclstring_equals(scl,s);
    if (ris == true)
        printf("True");
    else
        printf("False");
        
    printf("\n");

    // 7.10
    sclstring_remove(&scl,val);
    sclstring_print(scl);
    printf("\n");
    
    return 0;
}

int emptySCL(TipoSCL scl){
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
        printf("%c\n", scl->info);
        writeSCL(scl->next);
    }
}

void sclstring_print(TipoSCL s){
    if (emptySCL(s))
        printf("");
    else
        writeSCL(s);
}

TipoSCL sclstring_create(const char *s){
    
    int len = strlen(s);

    TipoSCL scl_vuota = (TipoSCL)malloc(sizeof(TipoNodoSCL));
    scl_vuota = NULL;

    for (int i=len; i>=0; i--)
        addSCL(&scl_vuota,s[i]);
    
    writeSCL(scl_vuota);

}

bool sclstring_equals(TipoSCL scl, const char *s){
    if (scl == NULL && *s == '\0')
        return true;
    else if (scl != NULL && *s=='\0' || scl==NULL && *s!='\0')
        return false;
    else{
        if (scl ->info == *s)
            return true && sclstring_equals(scl->next, s+1);
        else
            return false && sclstring_equals(scl->next,s+1);
    }    
}

void sclstring_remove(TipoSCL *scl_p, char val){
    if ((*scl_p) == NULL)
        return;
    else if ((*scl_p)->info == val){
        TipoSCL temp = *scl_p;
        (*scl_p) = temp->next;
        free(temp);
    }
        else
            scl_p = &((*scl_p)->next);

        return sclstring_remove(scl_p,val);
}