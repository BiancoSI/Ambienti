#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// legge  un vettore da un file binario
#define N 10
int main()
{	
	int vett[N];	int fd;
	int i;
	fd=open ("vettore.bin", O_RDONLY);
	if (fd==-1){
		printf("Errore nella apertura del file\n");
		exit(1);
	}
	read (fd, vett,N*sizeof(int));
	close (fd);
	for (i=0;i<N;i++)
		printf("%d\t",vett[i]);
	printf("\n");
	return 0;

}
