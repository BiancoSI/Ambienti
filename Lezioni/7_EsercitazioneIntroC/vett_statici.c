#include <stdio.h>
#define N 10

int main(){
	/* dichiarazioni */
	int i;
	int v[N];
	
	/* lettura da input */
	for(i=0; i<N; i++){
		printf("inserire il valore v[%d] ", i);
		scanf("%d", &v[i]);
	}	
	
	/* scrittura di un file*/
	for(i=0; i<N; i++){
		printf("v[%d]=%d \n", i, v[i]);
	}
	return 0;
}
