#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{	int fd;
	char  nome[100];
	fd=open("ciao.txt", O_RDONLY);
	if (fd==-1){
		printf("Errore nell'apertura del file\n");
		exit(1);
	}
	read (fd, nome,100); 
	close (fd);
	printf("Nome=%s	\n",nome);
	return 0;

}
