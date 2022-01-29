#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define F 2
#define L 44

void crea(){
  int fd; int lunghezza; int numEle;
  char stringa[]="In questa stringa sono presenti 3 lettere a.";
  fd= open("Lettera.txt", O_WRONLY|O_CREAT, 0644);
  write(fd, stringa, sizeof(char)*strlen(stringa));
  lunghezza = lseek(fd, 0, SEEK_END);
  numEle= (int) lunghezza/sizeof(char);
  printf("%d", lunghezza);
  close(fd);
}
int main() {
  int pid, i;
  int fP[2];
  int da, a;
  int porzione;
  char daC='a';
  /*...........*/
  if ( pipe (fP)<0 ){
    printf("Errore generazione pipe\n");exit(1);
  }

  porzione= L/F;
  for (i=0, pid=1; i<F && pid>0 ; i++){
    da=i*porzione; a=da+porzione;
    pid=fork();
  }
  /*.............*/

  if (pid <0 ){
    printf("Erroe generazione processo\n"); exit(1);
  }
  if(pid > 0){//Padre
    int totale;
    int status;
    int x;

    for (i=0; i<F; i++){
      wait(&status);
    }
    close(fP[1]);
    for (i=0, totale=0; i<F; i++){
      read(fP[0], &x, sizeof(int));
      totale+=x;
    }
    close(fP[0]);
    printf("Il totale di lettere 'a' in Lettera.txt è : %d\n", totale);
  }else{ //Figli
    int fd;
    int occ=0;
    char let;

    fd=open("Lettera.txt", O_RDONLY);
    if (fd <0){
      printf("Errore apertura file Lettera.txt\n"); exit(1);
    }
    lseek(fd, da*sizeof(char), SEEK_SET);
    for (i=da; i<a; i++){
      read(fd, &let, sizeof(char));
      printf("%c\n", let);
      if ( daC == let){
        occ++;
      }
    }
    close(fP[0]);
    write(fP[1], &occ, sizeof(int));
    close(fP[1]);
    exit(1);
  }
  return 0;
}
