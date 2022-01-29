#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 5
int main(){
	int pd[2];
	int pdF[2];
	int pid, status;
	double ris;
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
		int i;
		int vet[N];
		for (i=0; i<N; i++)
			scanf("%d", &vet[i]);
		close(pd[0]);//Chiude il canale in lettura
		write(pd[1], vet, N*sizeof(int));
		close(pd[1]);
		
		wait(&status);
		
		close(pdF[1]);
		read(pdF[0], &ris, sizeof(double));
		close(pdF[0]);
		
		printf("Media del vettore %.3lf\n", ris);
	}else
	if (pid==0){
		int i;
		double media=0;
		int v[N];
		close(pd[1]);
		read(pd[0], v, N*sizeof(int));
		close(pd[0]);
		for (i=0; i<N; i++){
			media=media+v[i];
		}
		media= media /N;
		close(pdF[0]);
		write(pdF[1], &media, sizeof(double));
		close(pdF[1]);
		exit(0);
	}
	return 0;
}
