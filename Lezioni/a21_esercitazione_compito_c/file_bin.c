#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// scrivo un vettore in un file binario
#define N 5
int main()
{	
	int vett[]={10,20,30,40,50};
	int fd;
	int i;
	fd=open ("vettore.bin", O_WRONLY|O_CREAT,0644);
	if (fd==-1){
		printf("Errore nella creazione del file\n");
		exit(1);
	}
	for (i=0;i<N;i++)
		write (fd,&vett[i],sizeof(int));
	// alternativa invece del for
	// write(fd,vett,N*sizeof(int));
	close(fd);
	
	
	return 0;

}
