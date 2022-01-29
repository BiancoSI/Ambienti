#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#define F 2
#define K 10
#define NUM 6.85

void crea(){
  int fd;
  float v[K]={10.99, 2.9, 1.09, 23, 14, 5.67, 17.7, 0.98, 89, 0.674};
  fd=open("Input.bin", O_WRONLY|O_CREAT, 0644);
  write(fd, v, sizeof(float)*K);
  close(fd);
}

int main(){
  int pid, i, numF;
  int pfa[2], pfb[2];
  int fap[2], fbp[2];
  if ( pipe (pfa) <0 || pipe (pfb) <0 ){
    printf("Errore generazione pipe\n");
    exit(1);
  }
  if(pipe (fap)<0 || pipe(fbp)<0){
    printf("Errore genrazione pipe\n");
    exit(1);
  }
  pid=1;
  for (i=0, numF=0; i<F && pid>0; i++){
    numF++;
    pid=fork();
  }

  if( pid<0){//FALLITO
    printf("Errore generazione figlio \n");exit(1);
  }else if (pid > 0){//PADRE
    crea();
    float tappo=0;
    int fd, status;
    int fdx;
    int fdy;
    int lunghezza, numElementi;
    char min[100], med[100];
    float media, minore, val;
    fd = open("Input.bin", O_RDONLY);
    lunghezza=lseek(fd,0, SEEK_END);
    numElementi=(int) lunghezza/sizeof(float);
    printf("Elementi : %d\n", numElementi);
    lseek(fd, 0, SEEK_SET);
    close(pfa[0]);
    close(pfb[0]);
    for (i=0; i<numElementi; i++){
      read(fd, &val, sizeof(float));
      if (val >= NUM){
          write(pfb[1], &val, sizeof(float));
      }else {
          write(pfa[1], &val, sizeof(float));
      }
    }
    write(pfa[1], &tappo, sizeof(float));
    write(pfb[1], &tappo, sizeof(float));
    close(pfa[0]);
    close(pfb[0]);
    close(fd);
    for (i=0; i<F; i++)
      wait(&status);
    close(fap[1]); close(fbp[1]);
    read(fap[0], &minore, sizeof(float));
    read (fbp[0], &media, sizeof(float));
    close(fap[0]); close(fbp[0]);
    sprintf(min, "%.3f", minore);
    printf("Minore %s\n", min);
    fdx = open("RisX.txt", O_WRONLY);
    fdy = open("RisY.txt", O_WRONLY);
    lseek(fdx, 5*sizeof(char), SEEK_SET);
    write(fdx, min, sizeof(char)*strlen(min));
    sprintf(med, "%.3f", media);
    printf("Media %s\n", med);
    write(fdy, med, sizeof(char)*strlen(med));
    close(fdx);
    close(fdy);
  }else {//FIGLIO
    if(numF == 1){//FA
      float val, min;
      close(pfa[1]);
      read(pfa[0], &val, sizeof(float));
      for(min=val; val!=0; read(pfa[0], &val, sizeof(float))){
        if(min> val){
          min=val;
        }
      }
      close(pfa[0]);
      close(fap[0]);
      write(fap[1], &min, sizeof(float));
      close(fap[1]);
      exit(1);
    }else {//FB
      float val, media;
      int num;
      close(pfb[1]);
      read(pfb[0], &val, sizeof(float));
      for(media=0, num=0; val!= 0; read(pfb[0], &val, sizeof(float))){
        media+=val;
        num++;
      }
      close(pfb[0]);
      if(num>0){
        media= media/num;
      }
      close(fbp[0]);
      write(fbp[1], &media, sizeof(float));
      close(fbp[1]);

      exit(1);
    }
  }
  return 0;
}
