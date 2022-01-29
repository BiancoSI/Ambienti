#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd;
	char nome1[]="Paolo Verdi";
	char nome2[]="Luca Bianchi";
	char buffer[100];
	int voto1 = 30;
	int voto2 = 28;
	fd=open("prova.txt", O_WRONLY|O_CREAT, 0644);
	
	if(fd==-1){
		printf("Errore\n");
		exit(1);
	}
	write(fd, nome1, strlen(nome1)*sizeof(char));
	sprintf(buffer, "\t%d\n", voto1);
	write(fd, buffer, strlen(buffer)*sizeof(char));
	
	write(fd, nome2, strlen(nome2)*sizeof(char));
	sprintf(buffer, "\t%d\n", voto2);
	write(fd, buffer, strlen(buffer)*sizeof(char));
	close(fd);
	return 0;
}
