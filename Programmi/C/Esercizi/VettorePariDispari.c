#include <stdio.h>
#include <stdlib.h>

void AllocaVettore(int *, int );
void StampaVettore(int *, int );
int PariODispariMaggiore(int *, int);


int main(){
	int dim;
	int *v;
	int s;
    
	printf("Dimensione v-->");
	scanf("%d", &dim);
	v= (int *) malloc(dim);
	if(v==NULL){ return 1;};
    
	AllocaVettore(v, dim);
	
	
	StampaVettore(v, dim);
	
	s=PariODispariMaggiore(v, dim);
	if(s){
		printf("La somma dei numeri Pari in v è maggiore di quella dei dispari\n");
	}else {
		printf("La somma dei numeri Dispari in v è maggiore di quella dei pari\n");
	}
	free(v);
}





void AllocaVettore(int *v, int dim){
	int i;
	for(i=0; i<dim; i++){
		printf("v[%d] <-- ", i);
		scanf("%d", &v[i]);
	}

}
void StampaVettore(int *v, int dim){
	int i;
	printf("V-->[ ");
	for(i=0; i<dim; i++){
		printf("%d  ", v[i]);
	}
	printf("]\n");
}

int PariODispariMaggiore(int *v, int dim){
	int pari, dispari, i;
	pari=0; dispari=0;
	for( i=0; i<dim; i++){
		if( v[i]%2 == 0){
			pari+=v[i];
		}else{
			dispari+=v[i];
		}
	}
	if(pari>dispari) { return 0;}
	else { return 1;}
}
