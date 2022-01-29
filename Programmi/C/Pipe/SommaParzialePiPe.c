#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 5
#define P 3
int main(){
	int pdPF[2];
	int pdFP[2];
	int i, pid;
	int inizio, fine;
	int porzione=N/P;
	int v[N]={10, 20, 30, 40, 50};
	pid=1;
	if( pipe(pdPF) <0|| pipe(pdFP)<0){
		printf("Errore \n"); exit(1);
	}
	for (i=0; i<P && pid>0; i++){
		if(i == P-1){
			inizio=i*porzione; fine=N-1;
		}else 
		{
			inizio=i*porzione; fine=inizio+porzione-1;
		}
		printf("inizio = %d fine = %d\n", inizio, fine);
		pid=fork();
	}
	if(pid >0){
		int ris=0, x=0, status;
		close(pdPF[0]);
		for (i=0; i<P; i++){
			write(pdPF[1], v, N*sizeof(int));
		}
 		close(pdPF[1]);
		close(pdFP[1]);
		for (i=0; i<P; i++){
			read(pdFP[0], &x, sizeof(int));
			ris+=x;
		}
		close(pdFP[0]);
		for (int i=0; i<P; i++){
			wait(&status);
		}
		printf("Ris == %d\n", ris);
	}else if(pid == 0){
		int vet[N];
		int somma=0;
		close(pdPF[1]);
		read ( pdPF[0], vet, N*sizeof(int) );
		close(pdPF[0]);
		for (i=inizio; i<=fine; i++){
			printf("v[%d]--> %d\n", i, vet[i]);
			somma+=vet[i];
		}
		printf("Pid : %d ha calcolato porzione %d - %d == %d\n", getpid(), inizio, fine, somma);
		close(pdFP[0]);
		write(pdFP[1], &somma, sizeof(int));
		close(pdFP[1]);
		exit(0);
	}
	return 0;
}
