#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} boolean;

boolean trovato(int [], int , int );

int main(){
	int v[]={12, 34, 5, 42};
	int length=4;
	int x;
	boolean found;
	/*
	printf("Lunghezza Vettore->");
	scanf("%d", &length);
	v=(int *)malloc(sizeof(int)*length);
	if(v==NULL) {
		printf("Errore. Impossibile allocare il vettore");
		exit(1);
	}
	for (int i=0; i<length; i++){
		printf("v[%d]->", i);
		scanf("%d");
	}
	*/
	printf("elemento da cercare-->");
	scanf("%d", &x);
	found = trovato(v, length, x);
	if (found) printf("Elemento presente.");
	else printf("Elemento non presente");
	printf("\n");
	return 0;
}

boolean trovato(int arr[], int length, int x){
	int i;
	boolean ePresente;
	ePresente=false;
	for (i=0; i<length && !ePresente; i++)
		if(arr[i]==x) ePresente =true;
	return ePresente;
}
