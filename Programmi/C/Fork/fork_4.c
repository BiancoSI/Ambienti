#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define FIGLI 32
int main(){
	int pid=1;
	int figli[FIGLI];
	int pidFigli[FIGLI];
	int status;
	int i=0;
	int time;
	for ( i=0; i<FIGLI && pid>0; i++){
		pid=fork();
		if(pid >0)
			figli[i]=pid;
		time=rand()%5;
	}
	if (pid ==0){
		printf("Processo %d  figlio di %d\n", getpid(),  getppid());
		sleep(time);
		exit(5);
	}
	if (pid >0){
		for (i=0; i<FIGLI; i++){
			pidFigli[i]=wait(&status);
			printf("Figlio %d ha terminato \n", pidFigli[i]);
		}
		printf("Tutti i figli hanno terminato\n");
	}
	
}
