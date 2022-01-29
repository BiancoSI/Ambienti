#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#define N 5
int main(){
	int pd[2];
	int pid ;
	if ( pipe(pd) <0){
		printf("Errore\n");
		exit(1);
	}
	pid=fork();
	if(pid==-1){
		printf("errore creazione processo");
		exit(1);
	}else
	if(pid>0){
		int x, status;
		char msg[20];
		scanf("%d", &x);
		close(pd[0]);//Chiude il canale in lettura
		for(int i=0; i<N; i++){
			write(pd[1], &x, sizeof(int));
			printf("Scrittura Su PIPE\n");
		}
		close(pd[1]);
		wait(&status);
	}else
	if (pid==0){
		int i, x;
		char msg[20];
		for(i=0; i<N; i++){
			close(pd[1]);
			read(pd[0], &x, sizeof(int));
			printf("Lettura PiPe ---> %d\n", x);
	}
		close(pd[0]);
		exit(0);
	}
	return 0;
}
