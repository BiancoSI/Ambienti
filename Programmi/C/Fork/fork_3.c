#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int pid,i, status ;
	int n=1;
	int figlio1, figlio2;
	pid=fork();
	if (pid >0){
		n=2;
		pid =fork();
	}
	switch (pid){
		case -1: printf("Errore \n"); exit (1); break;
		case 0: printf("Figlio del processo %d con pid --> %d\n", getppid(), getpid());sleep(5);exit(5); break;
		default :
			
			printf ("Processo padre %d aspetta i figli \n ", getpid());
			figlio1=wait(&status);
			printf("Terminato il processo %d con codice %d\n", figlio1, status/256);
			figlio2=wait(&status);
			printf("Terminato il processo %d con codice %d\n", figlio2, status/256); break;
	}
	/*
	if (pid <0 ) {
		printf("Fork fallita !!\n");
		exit(1);
	}else if (pid ==0){
		printf("Figlio del processo %d con pid --> %d\n", getppid(), getpid());
		sleep(5);
		exit(5);
	}else {
		pid=fork();
		if (pid <0 ) {
		printf("Fork fallita !!\n");
		exit(1);
		}else if (pid ==0){
			printf("Figlio del processo %d con pid --> %d\n", getppid(), getpid());
			sleep(1);
			exit(2);
		}else {
			int figlio1, figlio2;
			printf ("Processo padre %d aspetta i figli \n ", getpid());
			figlio1=wait(&status);
			printf("Terminato il processo %d con codice %d\n", figlio1, status/256);
			figlio2=wait(&status);
			printf("Terminato il processo %d con codice %d\n", figlio2, status/256);
		}
	}
	*/
}
