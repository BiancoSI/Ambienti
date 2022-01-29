#include <stdio.h>
#include <stdlib.h>

typedef enum{false,true} boolean;

float ** create(int, int);
void read(float** m,int , int);
void print(float** m,int , int);
float minimo_ottimo(float** ,int, int, float*);
boolean is_meta(float**,int,int,float);

int main(){
	float ottimo;
	int r,c,i;
	float** mat;
	float  mini;
	printf("dammi la dimensione delle righe\n ");
	scanf("%d",&r);
	printf("dammi la dimensione delle colonne\n ");
	scanf("%d",&c);
	mat=create(r,c);
	read(mat,r,c);
	print(mat,r,c);
	ottimo=minimo_ottimo(mat,r,c,&mini);
	printf("\n il minimo della matrice data è: %f\n", mini);
	if (ottimo!=-1)
		printf ("esiste un ottimo non doppio di valore %f\n",ottimo);
	else
		printf("ottimo non doppio inesistente\n");
	printf("libero spazio di memoria\n");
	for (i=0;i<r;i++)
		free(mat[i]);
	free(mat);
	return 0;
}

float** create(int r, int c){
	int i, j;
	float ** m =(float**)malloc(r*sizeof(float*));
	if(m==NULL){
		printf ("spazio non disponibile\n");
		exit(-1);
	}
	for(i=0;i<r;i++){
		m[i]=(float*)malloc(c*sizeof(float));
		if (m[i]==NULL){
			printf ("spazio non disponibile\n");
			for(j=0; j<i; j++)
				free(m[j]);
			free(m);
			exit (-1);
		}
	}
	return m;
}

void read(float**m, int r, int c){
	int i,j;
	printf("lettura elementi matrice\n");
	for (i=0;i<r;i++)
		for(j=0;j<c;j++){
			printf("dammi l'elemento m[%d][%d]  ",i,j);
			scanf("%f",&m[i][j]);
	}
}

void print(float ** m, int r, int c){
	int i,j;
	printf("la matrice data è:");
	for (i=0;i<r;i++){
		printf("\n");
		for(j=0;j<c;j++)
			printf("%f\t",m[i][j]);
	}
}

float minimo_ottimo(float** m,int r, int c, float* mini){
	int i,j;float maxmeno2=0;
	float ottimo;
	boolean meta=true;
	int valmeta=-1;
	float max=m[0][0];
	float min=m[0][0];
	for (i=0;i<r;i++)
		for(j=0;j<c;j++){
			if(m[i][j]<min)
				min=m[i][j];
			if(m[i][j]>max)
				max=m[i][j];
		}
	*mini=min;
	maxmeno2=max-2;
	printf ("maxmenodue=%f max=%f\n",maxmeno2,max);
	for (i=0;i<r&&meta;i++)
		for(j=0;j<c&&meta;j++){
			if(m[i][j]!=max && m[i][j]>=maxmeno2){
				meta=is_meta(m,r,c,m[i][j]/2);
				if (!meta)
					valmeta=m[i][j];
			}
		}
	return valmeta;
}

boolean is_meta(float** m,int r,int c,float val){
	int i,j;
	//printf("val = %f\n",val);
	for (i=0;i<r;i++)
		for(j=0;j<c;j++)
			if(m[i][j]==val)
				return true;
	return false;
}
