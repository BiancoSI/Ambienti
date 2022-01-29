#include <stdio.h>
#include <stdlib.h>

void AllocaVettore(double *, int);
void trovaMax(double*, double *, int*, int);
void StampaVettore(double *, int );

int main(){
	int dim, pos;
	double max;
	double *v;
	printf("Dimensione v >>");
	scanf("%d", &dim);
	v = (double *) malloc(dim*sizeof(double));
	if ( v== NULL){ return 1;}
	
	AllocaVettore(v, dim);
	StampaVettore(v, dim);
	//max=0; pos=0;
	trovaMax(v, &max, &pos, dim);
	printf(" Max= %.3lf nella posizione %.d.\n", max, pos);
    free(v);
	return 0;
}

void AllocaVettore(double *v, int dim){
	int i;
	for( i=0; i<dim; i++){
		printf("v[%d]-->", i);
		scanf("%lf", &v[i]);
	}
}
void StampaVettore(double *v, int dim){
    int i;
	printf(" v-> [");
	for( i=0; i<dim; i++){
		printf("  %.3lf  ", v[i]);
	}
	printf("]\n");
}

void trovaMax(double *v, double *max, int *pos, int dim){
	int i;
	*pos=0;
	*max=v[0];
	for ( i=0; i<dim; i++ ){
		if (*max<v[i]){
			*max=v[i]; *pos=i;
		}
	}
}
