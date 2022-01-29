#include <stdio.h>
#include <stdlib.h>

double** create (int , int);
void erase (double **, int );
void read (double **, int, int);
void print( double **,int , int);
void media_tutti_positivi(double **, int , int , double*, int*);

int main(){
	int n, m;
	int pos;
	double media;
	printf("Numero di righe>");
	scanf("%d", &n);
	printf("Numero di colonne>");
	scanf("%d", &m);
	double **mat=create(n, m);
	
	read(mat, n, m);
	
	print(mat, n, m);
	
	media_tutti_positivi(mat, n, m, &media, &pos);
	
	if(!pos){
		printf("La matrice è composta da soli numeri positivi");
		printf("La media della matrice =%.3lf", media);
	}
	else printf("La matrice contiene numeri maggiori e minori di 0");
	
	
	printf("\n");
	erase(mat, n);
	return 0;
}
double** create (int n, int m){
	int i,j;
	double **mat;
	mat=(double **)malloc(sizeof(double*)*n);
	if (mat==NULL) {
		printf("Errore. Matrice non allocata\n");
		exit(1);
	}
	for (i=0; i<n; i++){
		mat[i]=(double *)malloc(sizeof(double)*m);
		if (mat[i] == NULL) {
			printf("Errore. riga %d non allocata", i);
			for (j=0; j<i; j++)
				free(mat[j]);
			free(mat);
			exit(1);
		}
	}
	return mat;
}
void erase (double** mat, int n){
	int i, j;
	for ( i=0; i<n; i++)
		free(mat[i]);
	free(mat);
}
void read (double ** mat, int n, int m){
	int i, j;
	for ( i=0; i<n; i++)
		for(j=0; j<m; j++){
			printf("Elemento [%d][%d]-->", i, j);
			scanf("%lf", &mat[i][j]);
		}
}
void print(double ** mat,  int n , int m){
	int i, j;
	for (i=0; i<n; i++){
		for (j=0; j<m; j++)
			printf("\t%.3lf", mat[i][j]);
		printf("\n");
	}
}
void media_tutti_positivi(double **mat, int n, int m, double* media, int* p){
	int i, j;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++){
			if( mat[i][j] <0 )
				*p=1;
			*media += mat[i][j];
		}
	*media=*media/(n*m);
}


