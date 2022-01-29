#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	int pid, status;//RICORDA pid contiene 0 se figlio else il pid del figlio
	int pidNonno, pidFiglio, pidNipote;
	int *pidN=&pidNipote;
	pid=fork();
	if (pid ==0){
		pidNonno=getppid();
		pid=fork();
		if (pid ==0){
			*pidN=getpid();
			printf("Sono il nipote di %d, figlio di %d e ho id > %d\n", pidNonno, getppid(), *pidN);
			sleep(2);
			exit(5);
		}
		if (pid >0){
			*pidN=pid;
			wait(&status);
			printf("Sono il figlio di %d, ho come figlio %d e sono >%d\n", getppid(), pid, getpid());
			exit(pid);
			
		}
	}
	
	if (pid >0){
			wait(&status);
			printf("Ho come figlio %d e nipote %d io sono %d\n", pid, *pidN, getpid());
		}
	
}
