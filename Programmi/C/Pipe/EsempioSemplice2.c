#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int pd[2];
	int pdF[2];
	int pid, x, status;
	if ( pipe(pd) <0 || pipe(pdF)){
		printf("Errore\n");
		exit(1);
	}
	pid=fork();
	if(pid==-1){
		printf("errore creazione processo");
		exit(1);
	}else
	if(pid>0){
		int ris=0;
		printf("X<--");
		scanf("%d", &x);
		close(pd[0]);//Chiude il canale in lettura
		write(pd[1], &x, sizeof(int));
		close(pd[1]);
		wait(&status);
		
		close(pdF[1]);
		read(pdF[0], &ris, sizeof(int));
		close(pdF[0]);
		printf("Ris == %d", ris);
	}else
	if (pid==0){
		close(pd[1]);
		read(pd[0], &x, sizeof(int));
		close(pd[0]);
		printf("Ricevuto X= %d\n", x);
		x=2*x;
		close(pdF[0]);
		write(pdF[1], &x, sizeof(int));
		close(pdF[1]);
	
		exit(0);
	}
	return 0;
}
