#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>
#define N 5
#define P 3

int main(){
	int pdFP[2];
	int i, pid, inizio, fine, porzione;
	int v[N]={10, 20, 30, 40, 50 };
	porzione=N/P;
	if ( pipe(pdFP) <0 ){
		printf("Errore creazione pipe\n");
		exit(1);
	}
	pid=1;
	for (i=0; i<P && pid >0 ; i++){
		if(i == P-1){
			inizio=i*porzione; fine=N-1;
		}else{
		inizio=i*porzione; fine=inizio+porzione-1;
		}
		pid=fork();
		//Controlli pid <0
	}
	if(pid>0){
		int ris, x, status;
		ris=0;
		close(pdFP[1]);
		for (i=0; i<P; i++){
			read(pdFP[0], &x, sizeof(int));
			ris+=x;
		}
		close(pdFP[0]);
		for(i=0; i<P; i++)
			wait(&status);
		printf("Somma %d\n", ris);
		
	}else if(pid ==0 ){
		int somma=0;
		int i;
		printf("Pid %d da %d a %d \n", getpid(), inizio, fine);
		for (i=inizio; i<=fine; i++){
			printf("v[%d]-->%d\n", i, v[i]);
			somma+=v[i];
		}
		close(pdFP[0]);
		write(pdFP[1], &somma, sizeof(int));
		close(pdFP[1]);
		exit(0);
	}
	return 0;
}
