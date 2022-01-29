#include <stdio.h>
#include <stdlib.h>

typedef enum {false, true} boolean;

float** create (int , int);
void read(float**, int , int);
void print(float**, int , int);
void minimo_o_ottimo(float**, int , int, float*, float*);
boolean meta(float **, int , int, float);
int main(){
  int r, c;
  float min, o_ottimo;
  float** mat;
  printf("Righe-->");
  scanf("%d", &r);
  printf("Colonne-->");
  scanf("%d", &c);
  mat=create(r, c);
  read(mat, r, c);
  print(mat, r, c);
  minimo_o_ottimo(mat, r, c, &min, &o_ottimo);
  printf("Il minimo della matrice è %.3f\n L'ottimo doppio è %.3f\n", min, o_ottimo);
}

float** create (int r, int c){
  int i, k;
  float** mat=(float**)malloc(r*sizeof(float*));
  if ( mat == NULL ){
    printf("Errore generazione matrice\n");
    exit(1);
  }
  for (i=0; i<r; i++){
    mat[i]=(float*)malloc(c*sizeof(float));
    if ( mat[i] == NULL ){
      printf("Errore generazione riga %d\n", i);
      for (k=0; k<i; k++){
        free (mat[k]);
      }
      free(mat);
      exit(1);
    }
  }
  return mat;
}
void read(float** mat , int r, int c){
  int i, j;
  for (i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("mat[%d][%d] = ", i, j);
      scanf("%f", &mat[i][j]);
    }
  }
}
void print(float** mat, int r, int c){
  int i, j;
  for (i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("\t %.3f", mat[i][j]);
    }
    printf("\n");
  }
}
void minimo_o_ottimo(float** mat, int r, int c, float* min, float* o_ottimo){
  int i, j;
  float max_meno_due, x;
  boolean ex_meta = true;
  *min=mat[0][0];
  float max= mat[0][0];
  for (i=0; i<r; i++){
    for (j=0; j<c; j++){
      if (*min > mat[i][j])
        *min=mat[i][j];
      if(max< mat[i][j])
        max=mat[i][j];
    }
  }
  max_meno_due=max-2;
  for ( i=0; i<r && ex_meta; i++ ) {
    for( j=0; j<c; j++ ) {
      x=mat[i][j];
      if (x >= max_meno_due && x != max ){
        ex_meta = meta(mat, r, c, x/2);
        if ( !ex_meta ){
          *o_ottimo=x;
          break;
        }
      }
    }
  }

}


boolean meta(float **mat, int r, int c, float x ){
  int i, j;
  for (i=0; i<r; i++){
    for ( j=0; j<c; j++){
      if ( x== mat[i][j])
        return true;
    }
  }
  return false;
}
