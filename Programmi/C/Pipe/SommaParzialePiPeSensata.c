#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define P 3

void riempi(int [], int);
int main(){
  int PF[2];
  int FP[2];
  int i, pid, inizio, fine, porzione;
  int dim;
  printf("Dimensione del vettore-->");
  scanf("%d",&dim );
  if( pipe(PF) <0 || pipe(FP) < 0){
    printf("Errore generazione pipe\n");exit(1);
  }
  pid=1;
  porzione=dim/P;
  for (i=0; i<P && pid>0; i++){
    inizio=i*porzione;
    if( i == P-1 ){
      fine=dim-1;
    }
    else {
      fine=inizio+porzione-1;
    }
    pid=fork();
    if(pid == -1){
      printf("Errore generazione processo\n");
      exit(1);
    }
  }

  if(pid>0){
    int v[dim];
    riempi(v, dim);
    int x, somma, status;
    somma = 0;
    close( PF[0] );
    write( PF[1], v, dim*sizeof(int) );
    close( PF[1] );

    for(i=0; i<P; i++)
      wait(&status);

      close(FP[1]);
    for (i=0; i<P; i++){

      read(FP[0], &x, sizeof(int));
      somma+=x;

    }
    close(FP[0]);

    printf("Somma --> %d\n", somma);
  }//PADRE
  else if(pid == 0){
    int somma, x;
    somma=0;
    close(PF[1]);
    for ( i = inizio; i <= fine; i++ ){
      read(PF[0], &x, sizeof(int));
      printf("pid : %d v[%d]-->%d\n",getpid(), i, x);
      somma+=x;
    }
    close(PF[0]);
    printf("pid: %d  inizio: %d fine: %d\n", getpid(), inizio, fine);
    close(FP[0]);
    write(FP[1], &somma, sizeof(int));
    close(FP[1]);
    exit(0);
  }//Figlio

}//main


void riempi(int v[], int d){
  int i;
  for(i=0; i<d; i++){
    printf("v[%d]<--", i);
    scanf("%d",&v[i] );
  }
}
