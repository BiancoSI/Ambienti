#include <stdio.h>
#include <stdlib.h>
void secretFunction()
{
	printf("Congratulationi!\n");
	printf("Sei entrato nella funzione segreta che avrebbe potuto fare di tutto!\n");
	exit(1);
}

void ripeti()
{
	char buffer[20];

	printf("Scrivi del testo:\n");
	scanf("%s", buffer);
	printf("Hai inserito: %s\n", buffer);	
}

int main()
{
	ripeti();

	return 0;
}
