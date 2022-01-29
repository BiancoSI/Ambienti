/*Scrivere un programma in C per la gestione di matrici di float, che contenga i seguenti metodi:
Una funzione create, che riceve due interi (dimensione di righe e colonne), crea una matrice delle dimensioni indicate, e restituisce il suo puntatore.
Un metodo read per la lettura di una matrice da tastiera.
Un metodo print per la stampa della matrice su output.
Un metodo punto_di_sella che restituisce (in maniera opportuna usando i puntatori) il valore, la riga e la colonna del primo punto
di sella presente nella matrice.
Si definisce punto di sella un elemento m[i,j] tale che esso risulti essere contemporaneamente il massimo fra tutti gli elementi
della riga i-esima e il minimo fra tutti gli elementi della colonna j-esima oppure risulti essere contemporaneamente
il minimo fra tutti gli elementi della riga i-esima e il massimo fra tutti gli elementi della colonna j-esima.  Il metodo ritorna false se non esistono punti di sella. Si consiglia di trovare tutti i massimi di una colonna e metterli in un vettore e fare lo stesso per i minimi delle righe. 
Il metodo main che dichiara e alloca la matrice  e invoca opportunamente i metodi precedenti.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum{false,true} bool;

float** create(int,int);
void erase(float**,int,int);
void print(float**,int,int);
void read(float**,int,int);
void create_random(float**m,int r,int c);
bool maxRiga(float**,int,int,int);
bool maxColonna(float**,int,int,int);
bool minRiga(float**,int,int,int);
bool minColonna(float**,int,int,int);
float puntoSella(float**,int,int,int*,int*);
float puntoSella_complessita_n_cubo(float**,int,int,int*,int*);


int main(){
	float **mat;
	float pSella;
	int r,c,i;
	int riga;
	int colonna;
	printf("Inserire il numero di righe della matrice:\n");
	scanf("%d",&r);
	printf("Inserire il numero di colonne della matrice:\n");
	scanf("%d",&c);
	mat=create(r,c);
	erase(mat,r,c);
	
	//lettura da tastiera
	//printf("Inserire gli elementi della matrice:\n");
	//read(mat,r,c);
	
	//invece di leggerla da tastiera, creo una matrice random
    srand(time(NULL));
    create_random(mat,r,c);
    	
	printf("Matrice letta:\n");
	print(mat,r,c);
	printf("\n");
	//versione ottimizzata complessità n quadro
	pSella=puntoSella(mat,r,c,&riga,&colonna);
	
	// provare la seconda versione con una matrice molto grande  e vedere quanto impiega rispetto all'altra versione (commentare la stampa della matrice però) 
	//(per esempio con il comando time puntoSella     con una matrice 5 mila x 5 mila, sul mio pc: 7 secondi contro 10 minuti, se aumentate a 10 mila ci vogliono delle ore)
	//pSella=puntoSella_complessita_n_cubo(mat,r,c,&riga,&colonna);
	if(pSella!=-1){
		printf("L'ultimo punto di sella trovato è %f che si trova nella riga %d e nella colonna %d\n",pSella,riga,colonna);
	}
	else{
		printf("La matrice specificata NON contiene punti di sella\n");
	}
	printf ("Libero la memoria... \n");
	for (i=0;i<r;i++){
		free(mat[i]);
	}
	free(mat);
	return 0;
}

float** create(int r,int c){
	float **m;
	int i;
	m=(float**)malloc(r*sizeof(float*));
	if (m==NULL){
        	printf("MEMORIA NON DISPONIBILE! \n");
        	exit (-1);
	}
	else{
        	for (i=0;i<r;i++){
            		m[i]=(float*) malloc (c*sizeof(float));
            		if (m[i]==NULL){
                		printf("MEMORIA NON DISPONIBILE! \n");
                		free(m);
                		exit(-1);
            		}
        	}
	}
	return m;
}

void erase(float**m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			m[i][j]=0;
		}
	}
}

void create_random(float**m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			m[i][j]=rand();   //inserice un numero intero random fra 0 e RAND_MAX
		}
	}
}

void read(float**m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("m[%d,%d]> ",i,j);
			scanf("%f",&m[i][j]);
		}
	}
}

void print(float**m,int r,int c){
	int i,j;
	for(i=0;i<r;i++){
		for(j=0;j<c;j++){
			printf("%.2f\t",m[i][j]);
		}
	printf("\n");
	}
}
bool minRiga(float** m, int r,int c, int i){
	int j;
	float min=m[i][0];
	for(j=0;j<c;j++){
		if(m[i][j]<min){
			min=m[i][j];
		}
	}
	
		return min;
}

bool minColonna(float** m, int r,int c, int j){
	int i;
	float min=m[0][j];
	for(i=0;i<r;i++){
		if(m[i][j]<min){
			min=m[i][j];
		}
	}
	
		return min;
}

bool maxRiga(float** m, int r,int c, int i){
	int j;
	float max=m[i][0];
	for(j=0;j<c;j++){
		if(m[i][j]>max){
			max=m[i][j];
		}
	}
	
		return max;
}

bool maxColonna(float** m, int r,int c, int j){
	int i;
	float max=m[0][j];
	for(i=0;i<r;i++){
		if(m[i][j]>max){
			max=m[i][j];
		}
	}
	
		return max;
}

float puntoSella(float** m,int r,int c, int* riga,int* colonna){
	// questa versione calcola in anticipo 4 vettori che contengono il massimo e il minimo di tutte le righe e  colonne, pertanto raggiunge una complessità di n^2
	float pSella=-1;
	bool trovato=false;
	int i,j;
	int *minrig, *maxrig, *mincol, *maxcol;
	
	minrig=(int *) malloc (r*sizeof(int));
	maxrig=(int *) malloc (r*sizeof(int));
	
	mincol=(int *) malloc (c*sizeof(int));
	maxcol=(int *) malloc (c*sizeof(int));
	for(i=0;i<r;i++){
		minrig[i]=minRiga(m,r,c,i);
		maxrig[i]=maxRiga(m,r,c,i);
	}
	for(j=0;j<c;j++){
		mincol[j]=minColonna(m,r,c,j);
		maxcol[j]=maxColonna(m,r,c,j);
	}
	for(i=0;i<r && !trovato;i++){
		for(j=0;j<c && !trovato ;j++){
			if ((minrig[i]==m[i][j] && maxcol[j])==m[i][j] || (maxrig[i]==m[i][j]&& mincol[j]==m[i][j])){
				trovato=true;
				printf("L'elemento della riga %d e della colonna %d è un punto di sella\n",i,j);
				*riga=i;
				*colonna=j;
				pSella=m[i][j];
			}
		}
	}
	
	return pSella;
}


float puntoSella_complessita_n_cubo(float** m,int r,int c, int* riga,int* colonna){
	// questa versione per ogni elemento della matrice ricalcola il massimo e il minimo della colonna, pertanto raggiunge una complessità di n^3, che non è accettabile
	float pSella=-1;
	bool trovato=false;
	int i,j;
	for(i=0;i<r && !trovato;i++){
		for(j=0;j<c && !trovato ;j++){
			if((minRiga(m,r,c,i)==m[i][j]  && maxColonna(m,r,c,j) ==m[i][j]) || (maxRiga(m,r,c,i)==m[i][j]  && minColonna(m,r,c,j)==m[i][j] )){
				printf("L'elemento della riga %d e della colonna %d è un punto di sella\n",i,j);
				*riga=i;
				*colonna=j;
				pSella=m[i][j];
			}
		}
	}
	return pSella;
}
