#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){
	int fd;
	char nome1[1000];
	fd=open("prova.txt", O_RDONLY);
	
	if(fd==-1){
		printf("Errore\n");
		exit(1);
	}

	read(fd, nome1, 1000);
	printf("Ho letto: \n");
	printf("%s\n", nome1);
	close(fd);
	return 0;
}
