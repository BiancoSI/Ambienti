#include <stdio.h>
#include <stdlib.h>

typedef enum{false, true} boolean;

double** create(int , int);
void read(double**, int , int);
void print(double**, int , int);
void ver_matrice(double**, int*, int, int, int , int*, int *);
boolean ePresente(double**, int , int , int);

int main(){
  int r, c, len;
  int i;
  int numR, numC;
  int *v;
  double** mat;
  printf("Lunghezza vettore: ");
  scanf("%d", &len);
  printf("Numero righe: ");
  scanf("%d", &r);
  printf("Numero  di colonne: ");
  scanf("%d", &c);
  v= (int*)malloc(sizeof(int)*len);
  mat = create(r, c);
  printf("Lettura Vettore ");
  for(i=0; i<len; i++){
    printf("\nv[%d] = ", i);
    scanf("%d", &v[i]);
  }
  read(mat, r, c);
  print(mat, r, c);
  ver_matrice(mat, v, r, c, len, &numR, &numC);
  printf("Numero di righe che rispettano la condizione : %d\n", numR);
  printf("Numero di colonne che verificano la condizione : %d\n", numC);
  return 0;
}
double** create(int r, int c){
  int i, k;
  double** m= (double**) malloc(sizeof(double*)*r);
  if( m== NULL ){
    printf("Errore generazione matrice \n"); exit(1);
  }
  for (i=0; i<r; i++){
    m[i]= (double*) malloc(sizeof(double)*c);
    if(m[i] == NULL){
      printf("Errore generazione della %d° riga\n", i);
      for(k=0; k<i; k++){
        free( m[k] );
      }
      exit(1);
    }
  }
  return m;
}
void read(double **mat, int r, int c){
  int i, j;
  for(i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("mat[%d][%d] = ", i, j);
      scanf("%lf", &mat[i][j]);
    }
  }
}

void print(double** mat, int r, int c){
  int i, j;
  for (i=0; i<r; i++){
    for(j=0; j<c; j++){
      printf("mat[%d][%d]= %.3f\t",i, j, mat[i][j]);
    }
    printf("\n");
  }
}

void ver_matrice(double** mat, int* v, int r, int c, int len, int* numR, int* numC){
  int i, j, k;
  boolean presente;
  int count=0;
  double mediaPari, mediaDisp;
  int numP, numD;
  for (i=0; i<r; i++){
    presente=true;
    for(k=0; k<len && presente; k++){
      presente = ePresente(mat, i, c, v[k]);
    }
    if( presente ){
      count++;
    }
  }
  *numR=count;
  count=0;
  for(j=0; j< c; j++){
    numP=0; numD=0;
    mediaDisp=0; mediaPari=0;

    for(i=0; i<r; i++){
      if( i%2 == 0){
        numP++;
        if( mat[i][j] >= 0){
          mediaPari+=mat[i][j];
        }else{
          mediaPari+= (mat[i][j] *-1);
        }
      }else{
        numD++;
        mediaDisp+=mat[i][j];
      }
    }
    if (numP == 0 ){
      mediaPari=0;
    }else{
      mediaPari=mediaPari/numP;
    }
    if( numD == 0){
      mediaDisp=0;
    }else{
      mediaDisp=mediaDisp/numD;
    }
    if(mediaPari > mediaDisp){
      count++;
    }
  }
  *numC=count;

}
boolean ePresente(double** mat, int i, int c, int val){
  int j;
  for ( j=0; j<c; j++ ){
  
    if( (int) mat[i][j] == val) return true;
  }
  return false;
}
