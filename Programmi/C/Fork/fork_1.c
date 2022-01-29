#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>



int main(){
	int pid;
	int x=20;
	printf("Prima della fork \n");

	pid=fork();
	
	if (pid==-1) {
		printf("Fork fallita miseramente \n");
		exit(1);
	}else
		if ( pid ==0) {
			printf("A Bello sono il figlio e mi chiamo %d.\nMio padre è %d\n",getpid(), getppid()); 
			x=-20;
			printf("X=%d\n", x);
			sleep(2);
		}
		else {
			printf("Padre --> %d\n con figlio %d\n", getpid(), pid); 
			printf("X=%d\n",x );
			sleep(1);
		}
	return 0;
}
