#include <stdio.h>
#include <stdlib.h>

int** create (int, int);
void read(int **, int, int);
void print(int **, int, int);
void verifica_vet_matrice(int **, int, int, int*, int*, int*);

int main(){
  int r, c, i;
  int matVerPos =0, matVerNeg =0 ;
  int *V;
  int **mat;
  printf("Righe :");
  scanf("%d", &r);
  printf("Colonne e lunghezza vettore :");
  scanf("%d", &c);
  mat=create(r,c);
  V=(int *)malloc(sizeof(int)*c);
  for (i=0; i<c; i++){
    printf("v[%d]<< ", i);
    scanf("%d", &V[i]);
  }
  read(mat, r, c);
  print(mat, r, c);
  verifica_vet_matrice(mat, r, c, V, &matVerPos, &matVerNeg);
  printf("Num di elementi che soddisfano la prima proprietà : %d. \nNum di elementi che soffisfano la seconda proprietà: %d. \n", matVerPos, matVerNeg);
  return 0;
}
int** create(int r, int c){
  int i, k;
  int **mat=(int **)malloc(sizeof(int *)*r);
  if ( mat == NULL ){
    printf("Errore creazione matrice.\n");
    exit(1);
  }
  for (i=0; i<r; i++){
    mat[i]=(int *)malloc(sizeof(int)*c);
    if( mat[i]==NULL ){
      for (k=0; k<i; k++)
        free(mat[k]);
      printf("Errore nel generare la %d° riga.\n", i);
      free(mat);
      exit(1);
    }
  }
  return mat;
}

void read(int **mat, int r, int c){
  int i, j;
  for(i=0; i<r; i++)
    for(j=0; j<c; j++){
      printf("mat[%d][%d]<< ", i, j);
      scanf("%d", &mat[i][j]);
    }
}
void print(int **mat, int r, int c){
  int i, j;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("\t %d", mat[i][j]);
    }
    printf("\n");
  }
}
void verifica_vet_matrice(int **mat, int r, int c, int *v, int *matVerPos, int *matVerNeg){
  int i, j;
  int almeno_ter=c/3;
  int pos , neg , count;
  for (j=0; j<c; j++){
    pos=0; neg=0;
    for (i=0; i<r; i++){
      if (i%2 == 0){
        if( mat[i][j] > 0 )
          pos++;
      }else if( mat[i][j] <0 )
        neg++;
    }
    if (pos > neg )
      *matVerPos=*matVerPos+1;
  }
  for (i=0; i<r; i++){
    count=0;
    for(j=0; j<c /*&& (j+ (almeno_ter- count ) )<=c*/ ; j++){
      if ( mat[i][j] < 0 && mat[i][j] > v[j] )
        count++;
    }
    if(count >= almeno_ter)
      *matVerNeg=*matVerNeg+1;
  }
}
