#include <stdio.h>
#include <stdlib.h>
void bubbleSort(int v[], int dim);
int main(){
	int length, i;
	printf("Inserire la lunghezza del vettore da ordinare>>");
	scanf("%d", &length);
	int *v=(int *)malloc(length*sizeof(int));
    
    //Esecuzione
	for(i=0; i<length; i++){
		printf("Inserire valore v[%d] >",i);
        scanf("%d", &v[i]);
	}
	printf("v [");
	for(i=0; i < length; i++){
        printf(" %d", v[i]);
    }
    printf(" ]\n");
	bubbleSort(v,length); 
    printf("v [");
	for(i=0; i < length; i++){
        printf(" %d", v[i]);
    }
    printf(" ]\n");
    free(v);
}

void bubbleSort(int v[], int dim){
	int i, scambio, fine, low, high, temp;
    
    
	fine =dim;
	scambio=1;
	i=0;
    while( i < dim && scambio){
        scambio=0;
        low=0;
        high=low+1;
        while( high < fine ){
            if (v[ low ] > v[ high ] ){
                scambio=1;
                temp=v[low];
                v[low]=v[high];
                v[high]=temp;
            }
            low++;
            high++;
        }
        i++;
        fine--;
    }
    
}
