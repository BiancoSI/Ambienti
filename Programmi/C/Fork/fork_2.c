#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(){
	int pid;
	int x=20;
	int status;
	printf("Prima della fork \n");

	pid=fork();

	if (pid==-1) {
		printf("Fork fallita miseramente \n");
		exit(1);
	}else
		if ( pid ==0) {//Figlio
			/*printf("X ereditata ->%d\n",x);
		        x=10;
			printf("X -->%d\n", x);	*/
			sleep(3);
			printf("Figlio %d in esecuzione\ncon padre %d \n", getpid(), getppid());
			exit(5);
		}
		else {//>0 Padre
			//printf("Processo padre %d aspetta fine processo Figlio %d\n", getpid(), pid);
			//int figlio;
			//figlio=wait(&status);
			//printf("Il figlio %d ha terminato con codice %d\nvalore x-->%d\n", figlio, status/256, x);
			printf("Padre %d finisce prima del figlio %d\n",getpid(), pid); 
		}
	return 0;
}
