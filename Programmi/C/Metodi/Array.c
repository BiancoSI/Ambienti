#include "Array.h"
#include <stdio.h>
#include <stdlib.h>

void AllocaInt(int v[], int length){
	int i;
	for (i=0; i<length; i++){
		printf("v[%d]->", i);
		scanf("%d", &v[i]);
	}
}
void AllocaDouble(double v[], int length){
	int i;
	for (i=0; i<length; i++){
		printf("v[%d]->", i);
		scanf("%lf", &v[i]);
	}
}
void printVectInt(int v[], int length){
    int i;
	printf("[");
	for(i=0; i<length; i++){
		printf(" %d ", v[i]);
	}
	printf("]");
}
void printVectDouble(double v[], int length){
    int i;
	printf("[");
	for(i=0; i<length; i++){
		printf(" %lf ", v[i]);
	}
	printf("]");
}

