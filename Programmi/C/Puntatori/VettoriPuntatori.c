#include <stdio.h>
#include <stdlib.h>
#define length 4

int main(){
    int i; int v [length];
    int *pv;
    for(i=0; i<length; i++){
        printf("Elemento in pos v[%d] : ", i);
        scanf ("%d", &v[i]);
    }
    pv=(int *)&v;
    for (i=0; i<length; i++){
        printf("v[%d]\n", *(pv+i));
    }
    printf("-------\n");
    for (i=0; i<length; i++){
        printf("v[%d]\n", *(pv++));
    }
    printf("-------\n");
    pv=v;
    for (i=0; i<length; i++){
        printf("v[%d]\n", pv[i] );
    }
    printf("-------\n");
}
