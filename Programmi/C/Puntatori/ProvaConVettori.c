#include <stdio.h>
#define length 5
int main(){
    int i; int boolean;int v[length];int x; int pos;
    
    for(i=0; i<length; i++){
        printf("Immettere valore intero della posizione v[%d] >>", i);
        scanf("%d", &v[i]);
    }
    printf("Immettere un elemento da cercare in v");
    scanf("%d", &x);
    pos=-1;
    boolean =0;
    for(i=0; i<length && pos <0 ; i++){
        if(v[i]==x){
            pos=i;
            boolean=1;
        }
    }
    if(boolean){
        printf("Valore %d trovato in posizione %d", x, pos);
    }else{ printf("Valore %d non è presente nell'array", x);
    }
    
}
