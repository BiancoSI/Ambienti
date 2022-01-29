#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// legge  con lseek
//{10,20,30,40,5656767,1900,2233344,567788889, 1234444445, 90000};
#define N 10
int main()
{	
	int fd;
	int i;
	int x1,x2,x3;
	int pos;
	int lungfile;
	fd=open ("vettore.bin", O_RDONLY);
	if (fd==-1){
		printf("Errore nella apertura del file\n");
		exit(1);
	}
	lseek(fd,2*sizeof(int),SEEK_SET);
	read (fd, &x1,sizeof(int));
	printf("Letto %d\n",x1);
	pos=lseek(fd,3*sizeof(int),SEEK_CUR);
	read(fd,&x2,sizeof(int));
	printf("Sto leggendo in posizione %d il numero %d\n",pos,x2);
	lseek(fd, (-3)*sizeof(int),SEEK_END); 
	read (fd,&x3,sizeof(int));
	printf("Letto terz'ultimo %d\n",x3);
	// calcolare la lunghezza di un file
	lungfile=lseek(fd, 0, SEEK_END);
	printf ("FILE lungo %d byte, %d interi\n",lungfile, (int)(lungfile/sizeof(int)));
	
	return 0;

}
