#include <stdio.h>
#include <stdlib.h>
#define NUM 58
#define IND 3
typedef enum{false, true} boolean;

double** create(int , int );
void read (double **, int, int);
void print(double**, int , int);
void verifica_vet_matrice(double**, double *, int , int , int ,int*, int*);

int main(){
	int i, n, m, matVerificato, vetControllato;
	matVerificato=0; vetControllato=0;
	double **mat;
	double *v;
	printf("Numero righe-->");
	scanf("%d", &n);
	printf("Numero Colonne-->");
	scanf("%d", &m);
	v=(double*)malloc(sizeof(double) *m);
	mat=create (n, m);
	read (mat, n,m);
	for (i=0; i<m; i++){
		printf("v[%d]<--", i);
		scanf("%lf", &v[i]);
	}
	print(mat, n, m);
	verifica_vet_matrice(mat, v, n, m, m, &matVerificato, &vetControllato);
	
	printf ("Colonne con elementi dispari tutti maggiori di %d : %d\nRighe tali che vale la proprietà v[j] < mat[i][j-%d] && v[j]>mat[i][j+%d]: %d\n",NUM,matVerificato,IND, IND, vetControllato );
	free(mat);
	free(v);
	return 0;
}

double** create (int n, int m){
	int i, k;
	double **mat=(double **)malloc(sizeof(double*)*n);
	if ( mat == NULL ) {
		printf("Impossibile istanziare la matrice!");
		exit(1);
	}
	for (i=0; i<n; i++){
		mat[i]=(double *) malloc(sizeof(double)*m);
		if(mat[i] == NULL){
			printf("Errore nell'istanziare la riga %d della matrice", i);
			for (k=0; k< i; k++)
				free(mat[k]);
			exit(1);
		}
	}
	return mat;
}

void read(double **mat, int n, int m){
	int i,j;
	for (i=0; i<n; i++)
		for (j=0; j<m; j++){
			printf("mat[%d][%d]<--", i, j);
			scanf ("%lf", &mat[i][j]);
		}
}

void print(double **mat, int n, int m){
	int i, j;
	for (i=0; i<n; i++){
		for (j=0; j<m; j++){
			printf("\t%.3lf", mat[i][j]);
		}
		printf("\n");
	}
}
void verifica_vet_matrice(double **mat, double *v, int n, int m, int k, int *matV, int *vetC){
	int i, j;
	boolean dispari=true;
	for (j=0; j<m; j++){
		dispari=true;
		for (i=0; i<n && dispari; i++){
			if ( (int)mat[i][j]%2 == 0 || mat[i][j] <=NUM){
				dispari=false;
			}
		}
		if (dispari) 
			*matV = *matV+1;
	}
	for (i=0; i<n; i++){
		dispari=true;
		for ( j=0; j<m && dispari; j++){
			if( j-IND >=0 || v[j]>=mat[i][j-IND])
				dispari=false;
			if ( j+IND < m || v[j] <=mat[i][j+IND]) 
				dispari=false;
		}
		if (dispari)
			*vetC=*vetC+1;
	}
}
