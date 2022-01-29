#include <stdio.h>
#include <stdlib.h>
#define VAR 4
void scambia(int *);

int main(){
	int i;
	int v[VAR];
	for ( i=0; i<VAR; i++) {
		printf("%d ° intero =", i+1);
		scanf("%d", &v[i]);
	}
	scambia(v);
	for ( i=0; i<VAR/2; i++){
		printf("v[%d] --> %d", i, v[i] );
	}
}

void scambia(int *v){
	v[0]=v[3];
	v[1]=v[2];
}
