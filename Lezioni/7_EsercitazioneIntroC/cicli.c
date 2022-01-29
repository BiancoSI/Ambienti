#include <stdio.h>
#define N 10

int main(){
	/* dichiarazioni */
	int i;
	
	printf("Hello world\n");
	printf("Questo è il mio primo programma scritto in C \n");
	
	for(i=0; i<N; i++){
		printf("ciao \n");
	}
	i=0; /*inizializzazione*/
	
	while(i<N){
		printf("ok\t");
		/* per evitare loop infiniti aggiornamento delle var per il conteggio */
		i=i+1;
	}
	printf("\n");
	return 0;
}
