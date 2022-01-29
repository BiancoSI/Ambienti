#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
// scrivo un vettore in un file binario
#define N 10
int main()
{	
	int vett[]={10,20,30,40,5656767,1900,2233344,567788889, 1234444445, 90000};
	int fd;
	int i;
	char buffer[1000];
	fd=open ("vettore.txt", O_WRONLY|O_CREAT,0644);
	if (fd==-1){
		printf("Errore nella creazione del file\n");
		exit(1);
	}
	for (i=0;i<N;i++)
		{    
		sprintf(buffer,"%d ",vett[i]);   
		write (fd,buffer,strlen(buffer));
		}
	close(fd);
	
	
	return 0;

}
