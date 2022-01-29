#include <stdio.h>
#include <stdlib.h>
#define TOT 2
double** create(int , int );
void read (double **, int, int);
void print(double **,int ,int);
void verifica_mat(double **, int *, int, int, int*, int*);

int main(){
  int r, c;
  int i;
  int numC=0, numR=0;
  int *v;
  double **mat;
  printf("Numero righe--> ");
  scanf("%d", &r);
  printf("Numero Colonne matrice e vettore --> ");
  scanf("%d", &c);
  mat=create(r, c);
  v= (int *)malloc(sizeof(int)*c);
  for (i=0; i<c; i++){
    printf("v[%d]-->", i);
    scanf("%d", &v[i]);
  }
  read(mat, r, c);
  print(mat, r, c);
  verifica_mat(mat, v, r, c, &numC, &numR);
  printf("Prima proprietà garantita da %d colonne\n", numC);
  printf("Seconda proprietà garantita da %d righe\n", numR);
  return 0;
}


double** create(int r, int c){
  int i, k;
  double **mat=(double **)malloc(sizeof(double*)*r);
  if (mat==NULL){
    printf("Errore generazione Matrice!\n");
    exit(1);
  }
  for(i=0; i<r; i++){
    mat[i]=(double*)malloc(sizeof(double)*c);
    if( mat[i]==NULL){
      printf("Errore generazione riga %d.\n", i);
      for(k=0; k<i; k++){
        free(mat[i]);
      }
      exit(1);
    }
  }
  return mat;
}

void read (double **mat, int r, int c){
  int i, j;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("mat[%d][%d]-->", i, j);
      scanf("%lf", &mat[i][j]);
    }
  }
}
void print(double **mat, int r, int c){
  int i, j;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("\t%.3lf", mat[i][j]);
    }
    printf("\n");
  }
}

void verifica_mat(double **mat, int *v, int r, int c, int *numC, int *numR){
  int i, j, count;
  double media=0;
  double somma=0;
  for (j=0; j<c; j++){
    count=0;
    for(i=0; i<r && count<TOT; i++){
      if (mat[i][j] == v[j])
        count++;
    }
    if(count>=TOT){
      *numC=*numC+1;
    }
  }
  for(i=0; i<r; i++){
    somma=0;
    for(j=0; j<c; j++){
      somma+=mat[i][j];
    }
    media=somma/c;
    if (somma<5*media)
      *numR=*numR+1;
  }
}
