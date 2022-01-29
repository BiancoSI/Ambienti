#include <stdio.h>
#include <stdlib.h>

int** create (int , int);
void read (int**, int, int);
void print(int**, int , int);
void processa_mat(int**, int[], int, int, int*, int* );
float Media(int *v , int m);

int main(){
  int n, m;
  int **mat; int *v;
  int numr, numc;
  int i;

  printf("Numero righe: ");
  scanf("%d", &n);
  printf("Numero Colonne: ");
  scanf("%d", &m);

  mat=create(n, m);
  v=(int*)malloc(sizeof(int)*m);
  for(i=0; i<m; i++){
    printf("v[%d] = ", i);
    scanf("%d", &v[i]);
  }
  read(mat, n, m);
  print(mat, n, m);
  processa_mat(mat, v, n, m, &numr, &numc);

  printf("Numero di Righe con Proprietà : %d\n",numr );
  printf("Numero di Colonne con Prorpietà : %d\n", numc);
  return 0;
}

int** create(int n, int m){
  int i, k;

  int **mat=(int**)malloc(sizeof(int*)*n);
  if(mat == NULL){
    printf("Errore allocazione della matrice \n");
    exit(1);
  }
  for( i =0 ; i<n; i++) {
    mat[i]=(int*)malloc(sizeof(int)*m);
    if ( mat[i] == NULL ){
      printf("Errore allocazione riga %d\n", i);
      for (k=0; k<i; k++){
        free(mat[k]);
      }
        exit(1);
    }
  }
  return mat;
}

void read(int **mat, int n, int m){
  int i, j;
  for(i=0; i<n; i++){
    for(j=0; j<m; j++){
      printf("mat[%d][%d] = ", i, j);
      scanf("%d", &mat[i][j]);
    }
  }
}

void print(int **mat, int n, int m){
  int i, j;
  for (i=0; i<n; i++){
    for(j=0; j<m; j++){
      printf("\t%d", mat[i][j]);
    }
    printf("\n");
  }
}
float Media(int *v, int m) {
  int i;
  float count=0;
  for(i=0; i<m; i++){
    count+=v[i];
  }
  return count/m;
}
void processa_mat(int **mat, int *v, int n, int m, int* numR, int *numC){
  int i, j;
  int count=0;
  float media;
  int max;
  int vale;

  for(i=0; i<n; i++){
    vale=1;
    for( j=0; j<m && vale; j++){
      if ( ( mat[i][j] %2 != 0 )  || mat[i][j]<=v[j])
        vale=0;
    }
    if(vale){
      count++;
    }
  }
  *numR=count;
  media=Media(v, m);
  count=0;
  for(j=0; j<m; j++){
    max=mat[0][j];
    for(i=0; i<n; i++){
      if ( max< mat[i][j]){
        max=mat[i][j];
      }
    }
    if(max>media )
    count++;
  }
  *numC=count;
}
