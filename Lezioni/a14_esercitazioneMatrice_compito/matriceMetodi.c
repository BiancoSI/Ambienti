#include <stdlib.h>
#include <stdio.h>

void leggiMat (int ** mat, int n, int m);
void scriviMat (int **mat, int n, int m);
int ** createMat ( int n, int m);


int main(){
  
int n, m,i,j;
n=3; m=4;
int **mat;
mat=createMat(n,m);
// lettura di una matrice
leggiMat(mat,n,m);		
// stampa di una matrice
scriviMat(mat,n,m);

return 0;

}

void leggiMat (int** mat, int n, int m)
{
int i,j;
for (i=0;i<n;i++)
        for (j=0;j<m;j++){
                printf ("Inserisci elem [%d][%d] >",i,j);
                scanf ("%d",&mat[i][j]);
        }
}

void scriviMat (int** mat, int n, int m)
{
int i,j;
for (i=0;i<n;i++){
        for (j=0;j<m;j++)
                printf ("%d\t",mat[i][j]);
        printf("\n");
	}
}

int** createMat ( int n, int m)
{
int i;
int **mat;
mat=(int **) malloc (sizeof(int*)* n);
if (mat==NULL){
// non sono riuscito ad allocare la memoria
        printf ("Matrice non allocata\n");
        exit(1);
}

for (i=0;i<n;i++)
        mat[i]=(int *) malloc (sizeof(int)*m);
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


