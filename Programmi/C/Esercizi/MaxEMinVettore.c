#include <stdio.h>
#include <stdlib.h>

void AllocaVettore(int *, int );
void StampaVettore(int *, int);
int Max(int[], int );
int min (int[], int);

int main() {
	int i, dim;
	int *v;
	printf("Dimensione vettore -->");
	scanf("%d", &dim);
	v= (int *) malloc(dim*sizeof(int));
	if(v==NULL){ return 1;}
	AllocaVettore(v, dim);
	StampaVettore(v, dim);
	printf("Il massimo in v --> %d\n",Max(v, dim) );
	printf("Il minimo in v--> %d \n", min(v, dim));

	return 0;
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

int Max(int *v, int dim){
	int i, max;
	max=v[0];
	for( i=1; i<dim; i++){
		if ( v[i]>max){
			max=v[i];
		}
	}
	return max;
}
int min(int *v, int dim){
	int i, min;
	min=v[0];
	for(i=1; i<dim; i++){
		if( min>v[i]){
			min=v[i];
		}
	}
	return min;
}


