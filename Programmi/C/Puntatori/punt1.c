#include <stdio.h>
#include <stdlib.h>

int main(){
    int x=10;
    int *px;
    
    px=&x;
    
    printf("Valore di x = %d\n", *px); 
    
    printf("Valore indirizzo di x = %p\n", &x);
    
    printf("Valore contenuto in px = %p\n", px);
    
    *px=50;
    printf("Valore di x modificato con *px = %d\n", *px);
    return 0;
}
