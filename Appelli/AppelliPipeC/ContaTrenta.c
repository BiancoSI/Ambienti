#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#define N 10


int main(){
  int pid, i, porzione;
  int fp[2];
  int da, a, fd;
  int lunghezza;
  if (pipe(fd) <0 ){
    printf("Errore generazione pipe.\n");
    exit(1);
  }
  fd = open ("voti.bin", O_RDONLY);
  if ( fd <0 ){
    printf("Errore apertura file\n");
    exit(1);
  }
  lunghezza = lseek(fd, 0, SEEK_END);
  numEle = (int) lunghezza / sizeof(int);
  close(fd);
  porzione = (int)numEle / N;

  pid=1;
  for ( i = 0; i < N && pid >0; i++){
    if ( i == N-1 ){
      da = a+1; a = numEle-1;
    } else {
      da = i*porzione;
      a = da+porzione-1;
    }
    pid=fork();
  }
  switch pid{
    case -1:
      printf("Errore generazione figli\n");
      exit(1);
      break;
    case 0:
      //FIGLIO
      int count=0;
      int x;
      fd=open("voti", O_RDONLY);
      if(fd <0){
        printf("Errore apertura file.\n");
        exit(1);
      }
      lseek(fd, da*sizeof(int), SEEK_SET);
      for (i=da; i<=a; i++){
        read(fd, &x, sizeof(int));
        if ( x == 30 )
          count++;
      }
      close(fd);
      close(fp[0]);
      write(fp[1], &count, sizeof(int));
      close(fp[1]);
      exit(1);
      break;
    case default://PADRE
      int status, count=0 , x;
      for(i=0; i<N; i++){
        wait(&status);
      }
      close(fp[1]);
      for(i=0; i<N; i++){
        read(fp[0], &x, sizeof(int));
        count+=x;
      }
      close(fp[0]);
      printf("Occorrenze del valore 30 : %d\n", count);
      break;
  }
  return 0;
}
