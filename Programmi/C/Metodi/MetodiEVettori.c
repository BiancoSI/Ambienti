#include <stdio.h>
#include <stdlib.h>
#include "Array.h"
int main(){
	int length;
	int *v;
	printf("Lunghezza v-->");
	scanf("%d", &length);
	v=(int *)malloc(length*sizeof(int));
	AllocaInt(v, length);
	printVectInt(v, length);
	return 0;
}
