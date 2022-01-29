#include <stdio.h>
#include <stdlib.h>

int main(){
    int length, i;
    int *v;
    printf("LunghezzaVettore :");
    scanf("%d", &length);
    v=(int *) malloc(length);
    for(i=0; i<length  ; i++){
        printf("Valore v[%d] :", i);
        scanf("%d", &v[i]);
    }
    
    for( i=0; i<length; i++ ){
        printf("Valore in pos v[%d]=%d\n", i, v[i] );
    }
    free(v);
    return 0;
}
