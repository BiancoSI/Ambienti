#include <stdio.h>
#include <stdlib.h>

typedef enum{false, true} boolean;

float** create(int , int);
void read(float**, int, int);
void print(float**, int , int);
boolean eMult (float** , int , int, float );
boolean Supera(float, int , float*);
void ver_mat(float**, float*, int, int ,int , int*, int*);

int main() {
  int r, c, len;
  int i;
  float *v;
  float** m;
  int numR, numC;
  printf("Numero righe = ");
  scanf("%d", &r);
  printf("Numero Colonne = ");
  scanf("%d", &c);
  printf("Lunghezza vettore = ");
  scanf("%d", &len);
  v=(float*)malloc(sizeof(float)*len);
  if ( v == NULL ){
    printf("Errore allocazione vettore\n");
    exit(1);
  }
  m=create(r, c);
  for(i=0; i<len; i++){
    printf("v[%d] = ", i);
    scanf("%f", &v[i]);
  }
  read(m, r, c);
  print(m, r, c);
  ver_mat(m, v, r, c, len, &numR, &numC);
  printf("Il numero di righe che rispettano la proprietà = %d", numR);
  printf("Il numero di colonne che rispettano la proprietà = %d", numC);
  return 0;
}

float** create(int r, int c){
  int i, k;
  float** m;
  m= (float**)malloc(sizeof(float*)*r);
  if (m == NULL) {
    printf("Errore allocazione matrice\n");
    exit(1);
  }
  for (i=0; i<r; i++){
    m[i]=(float*)malloc(sizeof(float)*c);
    if( m[i] == NULL ){
      printf("Errore allocazione della %d° riga\n", i);
      for( k=0; k<i; k++){
        free(m[k]);
      }
      free(m[i]);
    }
  }
  return m;
}

void read(float** m, int r, int c){
  int i, j;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("m[%d][%d] = ", i, j);
      scanf("%f", &m[i][j]);
    }
  }
}

void print(float** m, int r, int c){
  int i, j;
  for( i=0; i<r; i++ ){
    for( j=0; j<c; j++ ){
      printf("\t%.3f", m[i][j]);
    }
    printf("\n");
  }
}
void ver_mat(float** m, float* v, int r, int c, int len, int *numR, int *numC){
  int i, j;
  int nr=0, nc=0;
  boolean mult, supera;
  for (i=0; i<r; i++){
    mult=true;
    for(j=1; j<c && mult; j+=2){
      mult = eMult(m, i, c , m[i][j]);
    }
    if ( mult ){
      nr++;
    }
  }
  *numR=nr;
  for(j=0; j<c; j++){
    supera=true;
    for(i=0; i<r && supera; i++){
      supera =Supera(m[i][j], len, v);
    }
    if(supera){
      nc++;
    }
  }
  *numC=nc;
}

boolean eMult(float** m, int r, int c, float val){
  int j;

  for(j=0; j<c; j+=2){
    if ( (int)val % (int)m[r][j] != 0){
      return false;
    }
  }
  return true;
}

boolean Supera(float val, int len, float* v){
  int i;
  for (i=0; i<len; i++){
    if ( val -5 > v[i]){
      return true;
    }
  }
  return false;
}
