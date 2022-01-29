#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#define L 10
typed enum {positivo, negativo} figlio;
int main(){
  int PFpos[2], PFneg[2];
  int FposP[2], FnegP[2];
  int pid, i;
  figlio f;
  int v[L];
  if ( pipe(PFpos) <0 || pipe(PFneg) < 0 pipe(FposP) <0 || pipe(FnegP) < 0){
    printf("Errore generazione pipe.\n")
    exit(1);
  }
  for (i=0; i<L; i++){
    printf("v[%d] = ", i);
    scanf("%d", &v[i]);
  }
  pid=1;
  for (i=0; i<2 && pid>0; i++){
      f=positivo+i;
      pid=fork();
      if(pid<0){
        printf("Errore generazione figlio\n");
        exit(1);
      }
  }
  switch (pid){
    case 0://figlio
      if ( f == positivo ){//Fpos
        float media=0;int x=1;
        close(PFpos[1]);
        int i=0;
        while(x>0){
          read(PFpos[0], &x, sizeof(int));
          if ( x> 0){
            media+=x;
            i++;
          }
        }
        close(PFpos[0]);
        media=media/i;
        close(FposP[0]);
        write(FposP[1], &media, sizeof(float));
        close(FposP[1]);
        exit(1);
      }else{//Fneg
          int Fn[2], nF[2];
          if (pipe(Fn) <0 || pipe(nF)<0 ){
            printf("Errore Generazione pipe\n");
            exit(-1);
          }
          pid=fork();
          switch (pid){
            case 0://nipote
              int x=-1;
              int min=1;
              close (Fn[1]);
              for (;x<0;){
                read(Fn[0], &x, sizeof(int));
                if(x<min)
                  min=x;
              }
              close(Fn[0]);
              close(nF[0]);
              write(nF[1], &min, sizeof(int));
              close(nF[1]);
              exit(1);
            break;
            default://Figlio negativo
              int x, status;
              close(Fn[0]);
              close(PFneg[1]);
              for(x=-1; x<0; ){
                read(PFneg[0], &x, sizeof(int));
                if(x<0)
                  write(Fn[1], &x, sizeof(int));
              }
              close(PFneg[0]);
              close(Fn[1]);
              wait(&status);
              if(status/256 == -1)
                {
                  printf("Errore Figlio\n");
                  exit(-1);
                }
              close(nF[1]);
              read(nF[0], &x, sizeof(int));
              close(nF[0]);
              close(FnegP[0]);
              write(FnegP[1], &x, sizeof(int));
              close(FnegP[1]);
              exit(1);
          }
          break;
      }
    break;
    default ://Sono il padre
      int tappo=0, status;
      float media=0;
      int min;
      close(PFpos[0]); close(PFneg[0]);
      for(i=0; i<L; i++){
        if ( v[i] <0 ) {
          write(PFneg[1], &v[i], sizeof(int));
        }
        if(v[i]>0){
          write(PFpos[1], &v[i], sizeof(int));
        }
      }
      write(PFpos[1], &tappo, sizeof(int));
      write(PFneg[1], &tappo, sizeof(int));
      close(PFpos[1]); close(PFneg[1]);
      wait(&status);
      wait(&status);
      close(FposP[1]);close(FnegP[1]);
      read(FposP[0], &media, sizeof(float));
      read(FnegP[0], &min, sizeof(float));
      close(FposP[0]);close(FnegP[0]);
      printf("Media num positivi : %.3f \n Minimo numeri negativi: %d\n", media, min);
  }
}
