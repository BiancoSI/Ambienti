//restituisce la media di tutta la matrice e un booleano che è True se gli elementi della matrice
// sono tutti positivi
#include <stdlib.h>
#include <stdio.h>

void leggiMat (double ** mat, int n, int m);
void scriviMat (double **mat, int n, int m);
double ** createMat ( int n, int m);
void tuttiPositivi(double** mat,int n, int m, double* media, int *tuttiPos);  

int main(){
  
int n, m,i,j;
double media;
int  tutti;
n=3; m=4;
double **mat;
mat=createMat(n,m);
// lettura di una matrice
leggiMat(mat,n,m);		
// stampa di una matrice
scriviMat(mat,n,m);
tuttiPositivi (mat, n, m, &media,&tutti);
printf ("Media=%.3f\n",media);
if (tutti)
	printf ("Elem. tutti positivi \n");
else
	printf ("NON tutti positivi \n");


return 0;

}

void leggiMat (double** mat, int n, int m)
{
int i,j;
for (i=0;i<n;i++)
        for (j=0;j<m;j++){
                printf ("Inserisci elem [%d][%d] >",i,j);
                scanf ("%lf",&mat[i][j]);
        }
}

void scriviMat (double** mat, int n, int m)
{
int i,j;
for (i=0;i<n;i++){
        for (j=0;j<m;j++)
                printf ("%.3f\t",mat[i][j]);
        printf("\n");
	}
}

double** createMat ( int n, int m)
{
int i;
double **mat;
mat=(double **) malloc (sizeof(double*)* n);
if (mat==NULL){
// non sono riuscito ad allocare la memoria
        printf ("Matrice non allocata\n");
        exit(1);
}

for (i=0;i<n;i++)
        mat[i]=(double *) malloc (sizeof(double)*m);
        if (mat[i]==NULL){
                int k=0;
                printf ("non ho allocato la riga %d\n",i);
                for (k=0;k<i;i++)
                        free (mat[k]);
                free (mat);
                exit(1);
	}
return mat;
}

void tuttiPositivi(double** mat,int n, int m, double* media, int *tuttiPos){
int i,j;
double somma=0;
for (i=0;i<n;i++)
	for (j=0;j<m;j++)
		somma=somma+mat[i][j];
*media=somma/(n*m);
*tuttiPos=1;
for (i=0;i<n&& (*tuttiPos);i++)
	for (j=0;j<m&& (*tuttiPos);j++)
		if (mat[i][j]<=0)
			*tuttiPos=0;
}
