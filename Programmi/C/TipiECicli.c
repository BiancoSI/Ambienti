#include <stdio.h>
#define length 10

int main(){
	/*Dichiarazione Variabili */
	int i; double d; float f; long l; int tmp; int boolean;
	
	printf("Immettere un numero intero>>");
	scanf("%d",&i);
	printf("Immettere un numero float>>");
	scanf("%f", &f);
	printf("L'intero è %d e il float è %.3f\n", i, f);
    tmp=0;
    while(tmp<length){
        printf("Prova Ciclo While %d\n",tmp);
        tmp++;
    }
    for(tmp=0; tmp<length; tmp++){
        if(tmp%2 == 0){
            printf("Turno Pari%d \n",tmp);
        }else{
            printf("Turno Dispari %d\n", tmp);
        }
    }
    tmp=(int)f;
    boolean=0;
    if(tmp%2 == 0){
        boolean=1;
    }
    if(boolean) {
        printf("Il numero %d ricavato da %.3f è pari",tmp, f);
    }else{
        printf("Il numero %d ricavato da %.3f è dispari",tmp, f);
    }
    printf("\n");
    return 0;
}
