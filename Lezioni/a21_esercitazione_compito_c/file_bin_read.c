#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// legge  un vettore da un file binario
#define N 5
int main()
{
	int vett[N];	int fd;
	int i;
	int pos, length, mezzo, num;
	int x;
	fd=open ("vettore.bin", O_RDONLY);
	if (fd==-1){
		printf("Errore nella apertura del file\n");
		exit(1);
	}
	read (fd, vett,N*sizeof(int));
	for (i=0;i<N;i++)
		printf("%d\t",vett[i]);
	printf("\n");

	pos=lseek(fd, 0, SEEK_CUR);
	printf("Posizione corrente = %d\n", pos);

	pos=lseek(fd, -1*sizeof(int), SEEK_CUR);
	printf("Posizione corrente = %d\n", pos);
	read(fd, &x, sizeof(int));
	printf("Ultimo numero: %d\n", x);

	length= lseek(fd, 0, SEEK_END); // in byte
	num=(int)(length/sizeof(int));
	printf("File lungo %d (byte) e %d (numeri)\n", length, num);

	printf("Ultimo - primo - a metà\n");
	pos=lseek(fd, -1*sizeof(int), SEEK_END);
	read(fd, &x, sizeof(int));
	printf("%d - ", x);

	pos=lseek(fd, 0*sizeof(int), SEEK_SET);
	read(fd, &x, sizeof(int));
	printf("%d - ", x);

	mezzo = (int) num/2;
	pos=lseek(fd, mezzo*sizeof(int), SEEK_SET);
	read(fd, &x, sizeof(int));
	printf("%d\n", x);

	close (fd);

	return 0;

}