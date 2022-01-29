#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define F 2


void creazioneFileBin();

int main(){
    int pf1[2], pf2[2], pn[2];
    int fp2[2];
    int nf, i, pid;
    if ( pipe(pf1)<0 || pipe(pf2)<0 || pipe(pn)<0 ){
      printf("Errore creazione pipe\n");
      exit(1);
    }
    if( pipe(fp2) <0 ){
      printf("Errore creazione Pipe\n");
      exit(1);
    }
    pid=1;
    for(i=0, nf=0; i<F && pid>0; i++){
      nf+=1;
      pid=fork();
    }
    if (pid==-1){
        printf("Errore creazione figlio\n"); exit(1);
    }else if( pid==0 ){
          printf("NF: %d\n", nf);
          if( nf == 1 ) {
            int fn[2];
            if( pipe(fn)<0 ){
              printf("Errore generazione pipe");
              exit(-1);
            }
            pid=fork();
            if( pid ==-1 ){
              printf("Errore creazione figlio\n"); exit(1);
            }else if(pid==0){
              //NIPOTE
                int val, x, count;
                int fd;
                float media;
                char buffer[100];

                close ( pn[1]);
                read( pn[0], &x, sizeof(int));
                close( pn[0] );

                close(fn[1]);
                for( read(fn[0], &val, sizeof(int)), count=0; val>0; read(fn[0], &val, sizeof(int)) ){
                  if(val<x){
                    count++;
                    media+=val;
                  }
                }
                close(fn[0]);
                if(count>0)
                  media = media/count ;
                else media=0;

                fd=open("Output.txt", O_WRONLY|O_CREAT, 0644);

                sprintf(buffer, "%f", media);
                write(fd, buffer, sizeof(char)*strlen(buffer));
                close(fd);
                printf("Nipote ha finito\n");
                exit(1);
              //NIPOTE
            }else{
              //F1
              printf("F1 ha iniziato\n");
                int val; int max;
                int tappo=-1;
                int status;
                close(pf1[1]);
                close(fn[0]);
                read(pf1[0], &val, sizeof(int));
                for(max=val; val>0; read(pf1[0], &val, sizeof(int)) ){
                  write(fn[1], &val, sizeof(int));
                  if(max<val){
                    max=val;
                  }
                }
                write(fn[1], &tappo, sizeof(int));
                close(fn[1]);
                close(pf1[0]);
                wait(&status);
                if(max<0){
                  printf("Errore");
                  exit(1);
                }else{
                  printf("Il massimo tra i valori dei numeri pari è %d", max);
                }
                printf("F1 ha finito\n");
                exit(1);
            }
        }else{//FIGLIO2
            printf("F2 ha iniziato\n");
            int val;
            int min;

            close(pf2[1]);
            read( pf2[0], &val, sizeof(int) );
            for( min=val; val>0 ; read( pf2[0], &val, sizeof(int) ) ){
              if(val<min)
                min=val;
            }
            close(pf2[0]);

            close(fp2[0]);
            write(fp2[1], &min, sizeof(int));
            close(fp2[1]);
            printf("F2 ha finito\n");
            exit(1);
          }//F2
      //FIGLI
    }else{
      //PADRE

        int x; int fd;
        int n, len;
        int status;
        int X;
        int tappo=-1;

        creazioneFileBin();

        fd=open("File.bin", O_RDONLY);
        len=lseek(fd, 0, SEEK_END);
        n = (int)len/sizeof(int) ;
        printf("Numero elementi := %d\n", n);
        lseek(fd, 0, SEEK_SET);
        close(pf1[0]);
        close(pf2[0]);
        for(i=0; i<n; i++){
          read(fd, &x, sizeof(int));
          if( x%2 == 0){
            write(pf1[1], &x, sizeof(int));
          }else{
            write(pf2[1], &x, sizeof(int));
          }
        }
        write(pf1[1], &tappo, sizeof(int));
        write(pf2[1], &tappo, sizeof(int));
        close(pf1[1]);
        close(pf2[1]);
        close(fd);

        printf("X= ");
        scanf("%d", &X);

        close(pn[0]);
        write(pn[1], &X, sizeof(int));
        close(pn[1]);

        for(i=0; i<F; i++){
          wait(&status);
        }
        close(fp2[1]);
        read(fp2[0], &x, sizeof(int));
        close(fp2[0]);
        if(x<0){
          printf("Errore file vuoto o contenente num negativi\n");
        }else
          printf("Il minore tra i numeri dispari è  %d\n", x);

    }//SWITCH
    return 0;
}//MAIN

void creazioneFileBin(){
  int v[10]={10, 5, 67, 54, 34, 22, 12, 89, 1234, 564};
  int fd=open ("File.bin", O_WRONLY|O_CREAT, 0644);
  write(fd, v, sizeof(int)*10);
  close(fd);
}
