#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd;
	char nome1[]="Mario Rossi";
	fd=open("prova.txt", O_WRONLY|O_CREAT, 0644);

	if(fd==-1){
		printf("Errore\n");
		exit(1);
	}
	write(fd, nome1, strlen(nome1)*sizeof(char));
	close(fd);
	return 0;
}
