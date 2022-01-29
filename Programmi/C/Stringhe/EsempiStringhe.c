#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
  int x;
  char *str1="SUKA ";
	char *str2="BLYAT";
	char str3;
	char str4[100];
  /*
	printf("Immettere una stringa>>");
  scanf("%s", str1);
  printf("Immettere una stringa>>");
  scanf("%s", str2);
  x=strcmp(str1, str2);
  if( x==0 ) printf("Le stringhe %s e %s sono uguali", str1, str2);
  else if (x <0) printf("La stringa %s precede %s", str1, str2);
  else printf("La stringa %s precede %s", str2, str1);
  printf("\n");
  sprintf(str3, "%s %s", str1, str2);
  printf("%s\n", str3);
  strcpy(str3, "Giovannino");
  printf("%s\n", str3);
  */
  x=10;
  sprintf(str4, "%s%s", str1, str2 );
  //x=strlen(str4);
  printf("%s\n",str4);
  return 0;

}
