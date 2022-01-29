#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
  int pf1[2];
  int pf2[2];
  int f1p[2];
  int f2p[2];
  int dim;
  int i, pid, nfiglio;
  if( pipe(f1p) <0 || pipe(f2p) <0 || pipe(pf1) <0 || pipe(pf2) <0 ){
    printf("Errore creaizone pipe.\n");
    exit(1);
  }
  pid=1;
  for(i=0; i<2 && pid>0; i++){
    nfiglio=i+1;
    pid=fork();
    if(pid <0 ){
      printf("Errore generazione figlio\n");
      exit(0);
    }
  }
  if(pid>0){
    int *v;
    int status;
    float media;
    int tappo=0;
    int max;
    printf("Dim vettore -->");
    scanf("%d", &dim);
    v=(int *)malloc(sizeof(int)*dim);
    for(i=0; i<dim; i++){
      printf("v[%d]<--", i);
      scanf("%d", &v[i]);
    }
    close(pf1[0]);
    close(pf2[0]);
    for (i=0; i<dim; i++){
      if(v[i]%2==0)
        write(pf1[1], &v[i], sizeof(int));
      if(v[i]%3==0)
        write(pf2[1], &v[i], sizeof(int));
    }
    write(pf1[1], &tappo, sizeof(int));
    write(pf2[1], &tappo, sizeof(int));
    close(pf1[1]);
    close(pf2[1]);
    for(i=0; i<2; i++){
      wait(&status);
    }
    close(f1p[1]);
    close(f2p[1]);
    read(f1p[0], &media, sizeof(float));
    close(f1p[0]);
    read(f2p[0], &max, sizeof(float));
    close(f2p[0]);
    printf("Media num  mul  di 2 --> %3.f, Max num mul di 3 --> %d\n", media, max);
  }else {
    if(nfiglio==1){//Media numeri %2
      float media=0;int x;
      close(pf1[1]);
      for(i=-1; x!=0 ;i++){
        read(pf1[0], &x, sizeof(int));
        media+=x;
      }
      if( i==0)
        i=1;
      close(pf1[0]);
      media=media/i;
      close(f1p[0]);
      write(f1p[1], &media, sizeof(float));
      close(f1p[1]);
      exit(0);
    }else if(nfiglio ==2){
      int max;int x;
      close (pf2[1]);
      read(pf2[0], &x, sizeof(int));
      if( x != 0)
        max=x;
      else
        max=-1;
      for(; x!=0;){
        read(pf2[0], &x, sizeof(int));
        if(max < x)
          max=x;
      }
      close(pf2[0]);
      close(f2p[0]);
      write(f2p[1], &max, sizeof(int));
      close(f2p[1]);
      exit(0);
    }
  }
}
