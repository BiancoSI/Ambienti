#include <stdio.h>
#include <stdlib.h>

double** create(int , int);
void print(double**, int , int);
void read(double**, int, int);
int punto_di_sella(double**, int, int, int*, int*, double*);

int main(){
	int n, m, i, j, pds;
	double val;
	printf("Righe: ");
	scanf("%d", &n);
	printf("Colonne: ");
	scanf("%d", &m);
	double **mat=create(n, m);
	read(mat, n, m);
	print(mat, n, m);
	pds=punto_di_sella(mat, n, m, &i, &j, &val);
	if( pds )
		printf("Punto di Sella mat[%d][%d] = %.3lf", i, j, val);
	else 
		printf("Non è presente alcun punto di sella");
	printf("\n");
	free(mat);
}

double** create(int n, int m){
	int i, j;
	double **mat=(double**)malloc(sizeof(double*)*n);
	if (mat == NULL) {
		printf("Errore, Matrice non instaziata");
		exit(1);
	}
	for (i=0; i<n; i++){
		mat[i]=(double*)malloc(sizeof(double)*m);
		if (mat[i] == NULL){
			printf("Errore, %d riga della matrice non istanziata", i);
			for (j=0; j<i; j++){
				free(mat[j]);
			}
			exit(1);
		}
	}
	return mat;
}
void print(double** mat, int n, int m){
	int i, j;
	for (i=0; i<n; i++){
		for(j=0; j<m; j++)
			printf("\t%.3lf", mat[i][j]);
		printf("\n");
	}
}
void read(double** mat, int n, int m){
	int i, j;
	for (i=0; i<n; i++)
		for(j=0; j<m; j++){
			printf("mat[%d][%d] =>",i, j);
			scanf("%lf", &mat[i][j]);
		}
}
int punto_di_sella(double** mat, int n, int m, int* r, int* c, double* val){
	int i, j, pds;
	double maxR, minR, maxC, minC;
	//MassimoPerRiga Mpr MinimoPerRiga mpr;
	//MassimoPerColonna Mpc MinimoPerColonna mpc;
	double * Mpr, *mpr;
	double* Mpc, *mpc;
	Mpr=(double*) malloc(sizeof(double)*n);
	mpr=(double*) malloc(sizeof(double)*n);
	Mpc=(double*) malloc(sizeof(double)*m);
	mpc=(double*) malloc(sizeof(double)*m);
	for (i=0; i<n; i++){
		maxR=mat[i][0];
		minR=mat[i][0];
		for (j=0; j<m; j++){
			if(mat[i][j] > maxR) maxR=mat[i][j];
			if(mat[i][j]<minR) minR=mat[i][j];
		}
		Mpr[i]=maxR;
		mpr[i]=minR;
	}
	for (j=0; j<m; j++){
		maxC=mat[0][j];
		minC=mat[0][j];
		for (i=0; i<n; i++){
			if (maxC < mat[i][j]) maxC=mat[i][j];
			if (minC > mat[i][j]) minC=mat[i][j];
		}
		Mpc[j]=maxC;
		mpc[j]=minC;
	}
	for (i=0, j=0; i<n && j<m ; i++, j++){
		printf("Riga %d colonna %d %.3lf , %3.lf | %.3lf , %.3lf \n",i,j, Mpr[i], mpc[j], mpr[i], Mpc[j]);
		if(Mpr[i] == mpc[j] || mpr[i] == Mpc[j]){
			pds=1;
			*r=i; *c=j; *val=mat[i][j];
			return pds;
		}
	}
	pds=0;
	return pds;
}
