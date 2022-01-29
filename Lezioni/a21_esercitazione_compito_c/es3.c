#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NUMFIGLI 3

void scrivi_voti(char nomeFile[100], int voti[], int n){
	int i, fd;
	printf("Scrivo file di voti\n");
	fd=open(nomeFile, O_WRONLY| O_CREAT, 0644);
	if(fd==-1){
		printf("Errore\n");
		exit(1);
	}
	for(i=0;i<n;i++){
		printf("%d\t", voti[i]);
	}
	printf("\n");
	// write di tutto il vettore
	write(fd, voti, n*sizeof(int));
	close(fd);
}

void codice_figlio(char nome_file[], int pd[], int inizio, int fine, int figlio){
	int fd; // file descriptor
	int i, voto, occ;
	close(pd[0]); //chiudo la pipe in ingresso
	fd=open(nome_file, O_RDONLY);
	if(fd==-1){printf("Errore nell'apertura del file\n"); exit(1);}
	// mi sposto sul file sulla posizione da cui iniziare a leggere
	lseek(fd, inizio*sizeof(int), SEEK_SET);
	occ=0;
	for(i=inizio;i<fine;i++){
		read(fd, &voto, sizeof(int));
		printf("Figlio %d: dal file leggo il voto %d\n",figlio, voto);
		if(voto==30)
			occ++;
	}
	close(fd);
	write(pd[1], &occ, sizeof(int));
	exit(0);
}

int main(){
	int fd;
	int lung_file, num_elementi;
	int pd[2]; // pipe descriptor
	int pid; // process id
	int pid_child; //process id del figlio
	int i, inizio, dim_proc, occ, status, fine, figlio;
	char nome_file[]="voti";
	int voti[]={20, 30, 23, 28, 30, 18};
	scrivi_voti(nome_file, voti, 6);
	//Lettura file
	fd=open("voti", O_RDONLY);	
	if(fd==-1){
		printf("Errore\n");
		exit(1);
	}
	// calcolo la lunghezza del file in byte
	lung_file=lseek(fd, 0, SEEK_END);
	num_elementi= (int)lung_file/sizeof(int);
	printf("Il file contiene %d elementi\n", num_elementi);
	dim_proc=num_elementi/NUMFIGLI;
	printf("Ogni processo figlio elaborerà %d elementi\n", dim_proc);
	close(fd);
	// creo la pipe
	if(pipe(pd)==-1){
		printf("Errore nella creazone della pipe\n");
		exit(1);
	}
	pid=10; // pid fittizio per entrare nel ciclo la prima volta
	// Generazione dei figli
	for(i=0; i<NUMFIGLI; i++){
		if(pid>0){ // sono il padre
			inizio=i*dim_proc;
			fine=inizio + dim_proc;
			figlio=i;
			pid=fork(); // genero un figlio
			if(pid==-1){
				printf("Errore nella fork\n");
				exit(1);
			}
		}
	}
	// Gestione processi padre e figli
	if(pid>0){ // sono il padre 
		int occ_tot=0;
		close(pd[1]); // chiudo la pipe in uscita
		// leggo le occorrenze parziali e calcolo il totale
		for(i=0; i<NUMFIGLI; i++){
			read(pd[0], &occ, sizeof(int));
			occ_tot+=occ;
			pid_child=wait(&status);
			printf("P: Il figlio %d ha terminato l'esecuzione\n", pid_child);
		}
		printf("P: Le occorrenze del voto 30 sono %d\n", occ_tot);
	}
	else if(pid==0){ // sono un figlio
		codice_figlio(nome_file, pd, inizio, fine, figlio);
	}
	
	return 0;
}
