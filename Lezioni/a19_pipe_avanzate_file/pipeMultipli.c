//Il padre legge un vettore da tastiera, quindi crea 2 figli F1 e F2, manda i numeri multipli di 2  al figlio F1, i multipli di 3 a F2. F1 calcola la media dei multipli di 2, mentre F2 calcola il massimo dei multipli di 3. Ritornano i risultati al padre.
//Per semplicita si suppone che non esista lo 0 fra i numeri letti.
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#define N 5
#define NFIGLI 2
int main(){
  
int n,i;
int vet[N];
int  PF1[2],PF2[2],F1P[2],F2P[2];
int  pid=10; int idFiglio;
int tappo=0;
int status, max_3;
double media_2;


if (pipe(PF1)==-1)
		{printf ("errore nel creare la pipe\n"); exit(1);}
if (pipe(PF2)==-1)
                {printf ("errore nel creare la pipe\n"); exit(1);}
if (pipe(F1P)==-1)
                {printf ("errore nel creare la pipe\n"); exit(1);}
if (pipe(F2P)==-1)
                {printf ("errore nel creare la pipe\n"); exit(1);}

//crea N Figli
for (i=0;i<NFIGLI;i++){
	if (pid>0){
		idFiglio=i+1;
		pid=fork();
	}
}

switch (pid){
	case -1: printf("errore nella creazione del processo\n");break;
	case 0: // i figli 
		if (idFiglio==1){ // codice primo figlio  medias
		double media;
		int somma=0,cont=0, num;
		read (PF1[0],&num,sizeof(int));
		while (num!=tappo){
			somma+=num; cont++;
			read (PF1[0],&num,sizeof(int));
		}
		if (cont==0)
			 media=0;
		else		
			media=(double)somma/cont;
		write (F1P[1],&media, sizeof(double));
		}
		else   {// codice secondo figlio
		int max,num;
		read (PF2[0], &num, sizeof(int));
		if (num==0)
		    	max=-1;
		else
			max=num;

		while (num!=tappo){
			if (num>max)
				max=num;
			read(PF2[0],&num,sizeof(int));
		}
		write (F2P[1],&max,sizeof(int));
		}
	break;
	default:  //codice padre
	
	for (i=0;i<N;i++){
		printf("Inserisci el %d>",i);
		scanf("%d",&vet[i]);
	}
	//passo i multipli ai due figli
	// dovrei fare le close  close (PF1[0])...
	for (i=0;i<N;i++)
		if (vet[i]%2==0)
			write (PF1[1],&vet[i],sizeof(int));
		else if (vet[i]%3==0)
			write (PF2[1],&vet[i],sizeof(int));
	write (PF1[1], &tappo, sizeof(int));		
	write (PF2[1], &tappo, sizeof(int));
	read (F1P[0], &media_2, sizeof(double));	
	read (F2P[0], &max_3, sizeof(int));
	printf ("Media dei Multipli 2=%.2f Massimo dei Multipli 3=%d\n",media_2,max_3);
	wait (&status);
	wait (&status); 	
}
return 0;

}

