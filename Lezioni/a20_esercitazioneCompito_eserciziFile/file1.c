#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{	int fd;
	fd=creat( "prova.txt",0664); 
	
	//rw- rw- r--
	//6    6   4	
	return 0;

}
