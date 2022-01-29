#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{	int fd;
	char  nome[]="Franco marroni";
	fd=open("ciao.txt", O_WRONLY|O_CREAT, 0644);
	if (fd==-1){
		printf("Errore nell'apertura del file\n");
		exit(1);
	}
	write (fd, nome,strlen(nome)*sizeof(char));
	close (fd);
	return 0;

}
