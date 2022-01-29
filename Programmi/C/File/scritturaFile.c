#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
  int fd, pos, i;
  char acapo[]="\n";
  char stringa[]= "Scrivo su testo!\n";
  char str2[]="Prova 2 su file testo\n";
  fd=open("File_testo.txt", O_WRONLY|O_CREAT, 0644);
  if (fd <0){
    printf("Errore apertura file\n");
    exit(1);
  }
  lseek(fd, sizeof(char)*5, SEEK_SET);
  write (fd, stringa, strlen(stringa)*sizeof(char));
  write(fd , str2, strlen(str2)*sizeof(char));
  close(fd);
}
