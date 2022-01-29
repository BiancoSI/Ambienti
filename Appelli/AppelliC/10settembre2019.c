#include <stdio.h>
#include <stdlib.h>

float** create (int , int );
void read(float **, int, int);
void print(float **, int , int);
int verifica_vet_matrice(float**, float*, int , int, int*);

int main(){
  int r, c, i, matGrande, vetPiccolo=0;
  float *v;
  float** mat;
  printf("Righe -->");
  scanf("%d", &r);
  v=(float*)malloc(sizeof(float)*r);
  printf("Colonne -->");
  scanf("%d", &c);

  for (i=0; i< r; i++){
    printf("v[i]= ");
    scanf("%f", &v[i]);
  }
  mat = create(r, c);
  read(mat, r, c);
  print(mat, r, c);
  matGrande=verifica_vet_matrice(mat, v, r, c, &vetPiccolo);

  printf("Numero fi Righe che rispettano la proprietà: %d \n", matGrande);
  printf("Numero di Colonne che rispettano la proprietà: %d \n", vetPiccolo);
  free(mat);
  return 0;
}

float** create(int r, int c){
  int i, k;
  float** mat=(float**)malloc(sizeof(float*) * r);
  if ( mat== NULL ){
    printf("Errore allocazione matrice\n");
    exit(1);
  }
  for (i=0; i<r; i++ ){
    mat[i]=( float* )malloc(sizeof(float)*c);
    if(mat[i] == NULL ){
      printf("Errore allocazione riga %d della matrice \n", i);
      for(k=0; k<i; k++){
        free(mat[k]);
      }
      exit(1);
    }
  }
  return mat;
}

void read(float** mat, int r, int c){
  int i; int j;
  for ( i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("mat[%d][%d]= ", i, j);
      scanf("%f", &mat[i][j]);
    }
  }
}
void print(float **mat, int r, int c){
  int i, j;
  for (i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("\t%.3f", mat[i][j]);
    }
    printf("\n");
  }
}

int verifica_vet_matrice(float **mat, float *v, int r, int c, int *vetP){
  int i, j, matG=0;
  int count;
  int limite=r/2;
  for ( i=1; i<r ; i+=2 ){
    int disp=i-1;
    count=0;
    for ( j=0; j<c && count<=limite; j++ ){
      if( mat[i][j] > mat[disp][j] ) count++;
    }
    if(count>limite){
      matG++;
    }
  }
  limite=c/2;
  for ( j=0 ; j < c ; j++ ){
    count=0;
    for( i=0; i<r ; i++ ){
      if ( mat[i][j] > v[i]) count++;
    }
    if(count > limite) *vetP=*vetP+1;
  }
  return matG;
}
