#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(){
  int fd;
  char stringa[100];
  fd=open("File_testo.txt", O_RDONLY);
  if (fd <0){
    printf("Errore apertura file\n");
    exit(1);
  }
  lseek(fd, 5, SEEK_SET);
  read (fd, stringa, sizeof(char)*100);
  printf("%s\n", stringa);
  close(fd);
}
