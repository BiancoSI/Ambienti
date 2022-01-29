#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define N 10
#define F 3

/*
Realizzare il seguente programma C che utilizzi le System Call di Linux. Un padre creerà 3 processi figli Fsum2 e FSum50, FsumAltri,
quindi leggera da  un file binario un vettore di 50 double.
Il padre leggerà i numeri a coppie, se la loro somma è maggiore di  50
li scriverà  al figlio Fsum50 se minore di 2 al figlio Fsum2, se no al figlio FSumAltri .
Fsum50 manderà solo i numeri maggiori di 200 a un nipote che calcolerà la media e la ritornerà a Fsum50, che la stamperà.
Fsum2 e FSumAltri calcoleranno invece il massimo dei numeri ricevuti e lo scriveranno sul file di testo Massimo.txt.
Si utilizzino le pipe che si ritengono necessarie per far comunicare i vari processi.
*/
void crea();
void codiceFsum50(int *, int);
void codiceFsum2(int *, int);
void codiceFsumAltri(int *, int);

int main(){
  crea();
  int pf50[2], pf2[2], pfa[2];
  int i, nf, pid;

  if ( pipe ( pf50 )<0 || pipe ( pf2 )<0 || pipe ( pfa )<0 ){
    printf("Errore generazione Pipe\n");
    exit(1);
  }

  pid=1;
  for (i =0; i<F && pid > 0; i++){
    nf=i;
    pid=fork();
  }
  if ( pid < 0){
    printf("Errore generazione processi\n");
    exit(1);
  }
  if ( pid > 0){
    int fd, status;
    int j, k;
    double val;
    double vettore[N];
    int mag_50=0;
    int min_2=0;
    int altri=0;
    double somma;

    fd=open("FileDouble.bin", O_RDONLY);
    for (i=0; i< N; i+=2){
        read(fd, &val, sizeof(double));
        somma = val;
        vettore[i] = val;
        read(fd, &val, sizeof(double));
        vettore[i+1]=val;
        somma+=val;
        if(somma > 50){
          mag_50+=2;
        }else if ( somma < 2 ){
          min_2+=2;
        }else {
          altri+=2;
        }
    }

    close(pf50[0]); close ( pf2[0] ); close( pfa[0] );
    write(pf50[1], &mag_50, sizeof(int) ); write ( pf2[1], &min_2, sizeof(int) );
    write (pfa[1], &altri, sizeof(int));
    for( i=0; i< N ; i+=2){
      val= vettore[i];
      somma=val;
      val=vettore[i+1];
      somma += val;
      if ( somma > 50 ){
        write(pf50[1], &vettore[i], sizeof(double));
        write(pf50[1], &vettore[i+1], sizeof(double));
      }else if ( somma < 2 ){
        write(pf2[1], &vettore[i], sizeof(double));
        write(pf2[1], &vettore[i+1], sizeof(double));
      }else{
        write(pfa[1], &vettore[i], sizeof(double));
        write(pfa[1], &vettore[i+1], sizeof(double));
      }
    }
    close( pf50[1] ); close ( pf2[1] ); close( pfa[1] );
    for (i=0; i<F; i++){
      wait(&status);
    }
  }else {
    if ( nf == 0){
      codiceFsum50(pf50, pid);
      exit(1);
    }else if (nf == 1){
      codiceFsum2(pf2, pid);
      exit(1);
    }else {
      codiceFsumAltri(pfa, pid);
      exit(1);
    }
  }
  return 0;
}

void crea(){
  int fd, i;
  double num=0;
  fd= open ("FileDouble.bin", O_WRONLY|O_CREAT, 0644);
  for (i=0; i<N; i++){
    printf("%.3lf\n", num);
    num = rand()%500 +1;
    if ( rand() % 2 != 0)
      num=num*-1;
    write(fd, &num, sizeof(double));
  }
  close(fd);
}

void codiceFsum50(int *pf50, int pid){
  int i;
  int np[2], pn[2];
  int numeri;
  double val;

  if( pipe ( np ) <0 || pipe ( pn ) < 0 ){
    printf("Errore generazione Pipe\n"); exit(1);
  }

  pid=fork();

  if (pid <0 ){
    printf("Errore generazione Processo\n");
    exit(1);
  }else if ( pid == 0 ){ // Nipote
    double media;

    close(np[1]);
    read(np[0], &numeri, sizeof(int));

    for(i=0, media=0; i<numeri; i++){
      read(np[0], &val, sizeof(double));
      media+=val;
    }
    close(np[0]);
    if (numeri > 0){
      media=media/numeri;
    }

    close(pn[0]); write (pn[1], &media, sizeof(double)); close( pn[1]);
    exit(1);
  }else {//Fsum50
    int status;
    int num;
    close (pf50[1]);
    read(pf50[0], &numeri, sizeof(int));
    double v[numeri];

    for (i=0, num=0; i < numeri; i++){
      read(pf50[0], &val, sizeof(double));
      if( val > 200 ){
        num++;
      }
      v[i]=val;
    }
    close(pf50[0]);

    close(np[0]);
    write(np[1], &num, sizeof(int));
    for(i=0; i< numeri; i++){
      if ( v[i] > 200 ){
        printf("Numeir in nipote : %.3lf \n", v[i]);
        write(np[1], &v[i], sizeof(double));
      }
    }
    close(np[1]);
    wait(&status);
    close(pn[1]);
    read(pn[0], &val, sizeof(double));
    close(pn[0]);

    printf("La media dei numeri maggiori di 200 è : %.3lf\n",val);
  }

}
void codiceFsum2(int *pf2, int pid){
  int length;
  int fd;
  char buffer[100];
  int i;
  double val=0, max;
  close (pf2[1]);
  read(pf2[0], &length, sizeof(int));
  if (length > 0){
    read(pf2[0], &val, sizeof(double));
  }
  for (i=0, max = val; i<length; i++){
    read(pf2[0], &val, sizeof(double));
    if (max < val) max=val;
  }
  if ( length == 0 ){
    sprintf(buffer, "Alcun numero per trovare il maggiore\n");
  }else
    sprintf(buffer, "%.3lf\n", max);
  fd= open("Massimo.txt", O_WRONLY|O_CREAT, 0644);
  write(fd, buffer, sizeof(char)*strlen(buffer));
  close(fd);
}
void codiceFsumAltri(int *pfa, int pid){
  int length;
  int fd, i;
  char buffer[100];
  double val, max;

  close(pfa[1]);
  read(pfa[0], &length, sizeof(int));
  if (length > 0){
    read(pfa[0], &val, sizeof(double));
  }
  for (i=0, max=val; i<length; i++){
    read(pfa[0], &val, sizeof(double));
    if (max< val) max=val;
  }
  close(pfa[0]);
  if (length== 0){
    sprintf(buffer, "Alcun numero per trovare il maggiore\n");
  }else{
    sprintf(buffer, "%.3lf\n", max);
  }
  fd = open("Massimo.txt", O_WRONLY|O_CREAT, 0644);
  write(fd, buffer, sizeof(char)*strlen(buffer));
  close(fd);
}
