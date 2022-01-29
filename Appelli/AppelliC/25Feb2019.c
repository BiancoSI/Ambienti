#include <stdio.h>
#include <stdlib.h>

int** create (int, int);
void read(int**, int , int);
void print(int**, int, int);
int somma_minima(int**, int, int, int*, int*);

int main(){
	int r, c;
	int **mat;
	int i, j;
	int val;

	printf("Numero di righe: ");
	scanf("%d", &r);
	printf("Numero di colonne: ");
	scanf("%d", &c);

	mat=create(r, c);

	read(mat,r, c);
	print(mat, r, c);

	val=somma_minima(mat, r, c, &i, &j);
	if ( i<0 ){
		printf("Nessun elemento corrispondente al punto di somma minimo\n");
	}else{
		printf("Punto di somma_minimo: mat[%d,%d]= %d \n", i, j, val);
	}
	free(mat);
	return 0;
}

int** create(int r, int c){
	int i, k;
	int ** mat;
	mat = (int**)malloc(sizeof(int*)*r);
	if (mat== NULL){
		printf("Errore allocazione matrice\n");
		exit(1);
	}
	for (i =0; i<r; i++){
		mat[i]=(int*)malloc(sizeof(int)*c);
		if ( mat[i] == NULL){
			printf("Errore allocazione riga %d\n", i);
			for (k=0; k<i; k++){
				free(mat[k]);
			}
			free(mat);
			exit(1);
		}
	}
	return mat;
}

void read(int** mat, int r, int c){
	int i, j;

	for (i=0; i<r; i++){
		for (j=0; j<c; j++){
			printf("mat[%d][%d]= ", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
}

void print(int **mat, int r, int c){
	int i, j;

	for( i=0; i<r; i++){
		for (j=0; j<c; j++){
			printf("%d\t", mat[i][j]);
		}
		printf("\n");
	}
}

int vale(int **mat, int r, int c, int i, int j, int val){
	int x, y, somma;

	for (y=0, somma=0; y<c; y++){
		somma+=mat[i][j];
	}
	if ( somma>= val)
		return 0;
	for (x=0; x<r; x++){
		if ( val >= mat[x][j] )
			return 0;
	}
	return 1;
}
int somma_minima(int **mat, int r, int c, int *riga, int *colonna){
	int i, j, ele;

	for(i=0; i<r; i++){
		for(j=0; j<c; j++){
			ele=mat[i][j]*c;
			if ( vale(mat, r, c,  i, j, ele) ){
				*riga=i; *colonna=j;
				return mat[i][j];
			}
		}
	}
	*riga=-1;
	*colonna=-1;
	return 0;
}
