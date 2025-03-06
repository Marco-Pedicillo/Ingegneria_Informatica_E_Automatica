#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str);
void print_chars(const char s[], const int idxs[], int dim);
char* select_chars(const char s[], const int idxs[], int dim);

int main(void){

    //4.5
    const char s[]= "puntatore";
    const int idxs[]= {1, 3, 5, 11};
    printf("prints chars..\n");
    print_chars(s,idxs,4);
    printf("\n\n");

    //4.6
    char *char_selected= select_chars(s,idxs,4);
    printf("%s", char_selected);
    printf("\n\n"); 

}

int my_strlen(const char *str){
    int i= 0;
    while (str[i]!= '\0')
        i++;
    
    return i;
}

void print_chars(const char s[], const int idxs[], int dim){

    int str_dim= my_strlen(s);
    for (int j= 0; j<dim; j++ ){
        int index= idxs[j];
        if (0<= index && index< str_dim)
            putchar(s[index]);
    }
}

char* select_chars(const char s[], const int idxs[], int dim){
    int str_dim= my_strlen(s);
    char *output_string= (char*)malloc((dim+1)*sizeof(char));
    int j2= 0;

    for (int j=0; j<dim; j++){
        int index= idxs[j];
        if (0<= index && index< str_dim){
            output_string[j2]= s[index];
            j2++;
        }
        output_string[j2]= '\0';
    }
    return output_string;
}