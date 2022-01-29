#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define N 50
#define F 2

void crea(){
    int fd ;
    int i;
    fd=open ("25Feb.bin",O_WRONLY|O_CREAT, 0644);
    for (i=0; i<N; i++){
        write(fd, &i, sizeof(int));
    }
    close(fd);
}

int main(){
	int pid, nf, i;
	int pf2[2], pf3[2];
	int f3p[2];

	if ( pipe (pf2) <0 || pipe (pf3)<0 || pipe (f3p)<0 ){
		printf("Errore allocazione pipe\n");
		exit(1);
	}

	pid=1;
	for (i=0; i< F && pid> 0; i++){
		nf=i;
		pid=fork();
	}

	if( pid < 0 ){
		printf("Errore generazione processo\n"); exit(1);
	}
	if ( pid > 0){ //Padre
		crea();
		printf("Inizio esecuzione Padre\n ");
		int fd, x, status ;
		char buffer[100], tappo[]="tappo";
		int tappo2 = 1, tappo3=2 ;

		fd=open("25Feb.bin", O_RDONLY);
		close (pf2[0]); close (pf3[0]);
		for(i=0; i<N; i++){
			read(fd, &x, sizeof(int));
			if ( x % 2 == 0){

				write(pf2[1], &x, sizeof(int));
			}else if ( x % 3 == 0){

				write(pf3[1], &x, sizeof(int));
			}
		}
		close(fd);
		write(pf2[1], &tappo2, sizeof(int));
		write(pf3[1], &tappo3, sizeof(int));
		close(pf2[1]); close(pf3[1]);

		for (i=0; i<F; i++){
			wait(&status);
		}
		printf("Finiti i figli\n");
		sleep(2);
		close ( f3p[1] );
		for(read(f3p[0], buffer, sizeof(char)*5); strcmp(buffer, "tappo") != 0; ){
			printf("%s\n", buffer);
			read(f3p[0], buffer, sizeof(char)*5 );
		}
		close ( f3p[0] );
		printf("Finita esecuzione Padre\n ");
	}
	if ( pid == 0) {

		if ( nf == 0){ //Fmul2
			printf("Inizio esecuzione Fmul2\n ");
			int fn[2];
			int tappo=1;
			int x, status;

			if ( pipe(fn) < 0 ){
				printf("Errore allocazione pipe\n"); exit(1);
			}
			pid =fork();
			if (pid<0){
				printf("Errore generazione Processo nipote\n");
				exit(1);
			}
			if( pid > 0){

				close(pf2[1]);
				close ( fn[0] );
				x=2;
				for( ; x %2 == 0; ){
					read ( pf2[0], &x, sizeof(int) );
					if ( x%2 == 0)
						write( fn[1], &x, sizeof(int) );
				}
				write( fn[1], &tappo, sizeof(int) );
				close( pf2[0] ); close ( fn[1] );
				wait( &status );
				exit( 1 );
				printf("Finita esecuzione Fmul2\n ");
			}else{ //Nipote
				printf("Inizio esecuzione Nipote\n ");
				int fd, val, count;
				char buffer[100];
				double media=0;

				close(fn[1]);
				val=2;
				for (count=0; val %2 ==0; ){
					read(fn[0], &val, sizeof(int));
					printf("val = %d\n", val);
					if(val %2 == 0){
						media+=val;
						count++;
					}
				}
				close(fn[0]);

				if (count != 0) media=media/count;

				fd = open("Media.txt", O_WRONLY|O_CREAT, 0644);

				sprintf(buffer, "%.3lf", media);
				write( fd , buffer, sizeof(char) * strlen(buffer));
				close(fd);
				printf("Finita esecuzione Nipote\n ");
				exit(1);
			}
		}else{ // Fmul3
			printf("Inizio esecuzione Fmul3\n ");
			char sup5[]="sup 5";
			char inf5[]="inf 5";
			char tappo[]="tappo";
			int val;

			close(pf3[1]);
			close(f3p[0]);
			for ( read (pf3[0], &val, sizeof(int)); val %3 == 0; ){
				if ( val > 5){
					write(f3p[1], sup5, sizeof(char)*strlen(sup5));
				}
				if (val < 5){
					write(f3p[1], inf5, sizeof(char) * strlen(inf5));
				}
				read( pf3[0], &val, sizeof(int));
			}
			write(f3p[1], tappo, sizeof(char)*strlen(tappo));
			close(f3p[1]); close(pf3[0]);
			exit(1);
			printf("Finita esecuzione Fmul3\n ");
		}

	}
    return 0;
}
