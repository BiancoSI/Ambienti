#include <stdio.h>
#define N 5

int main(){
	/* dichiarazioni */
	int i;
	int v[N];
	int val;
	int trovato;
	int pos;
	
	/* lettura da input */
	for(i=0; i<N; i++){
		printf("inserire il valore v[%d] ", i);
		scanf("%d", &v[i]);
	}	
	
	/* scrittura di un file*/
	for(i=0; i<N; i++){
		printf("v[%d]=%d \n", i, v[i]);
	}
	
	printf("inserire il valore dell'elemento da cercare ");
	scanf("%d", &val);
	
	trovato = 0; /* false*/
	for(i=0; i<N && !trovato; i++){
		if(v[i]==val){
			trovato=1; /* true */
			pos=i;	
		}
	}
	if(trovato){
		printf("il valore %d è presente nel vettore in posizione %d\n", val, pos);
	}
	else
		printf("il valore %d non è presente nel vettore\n", val);
	
	
	return 0;
}
