#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define NUMFIGLI 3

void scrivi_voti(char nomeFile[], int voti[], int n){
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

void codice_figlio(int pd_P_F[], int pd_F_P[], int voto_da_contare){
	int voto, occ;
	occ=0;
	close(pd_P_F[1]); //chiudo la pipe in uscita
	read(pd_P_F[0], &voto, sizeof(int));
	while(voto!=0){
		occ++;
		read(pd_P_F[0], &voto, sizeof(int));
	}
	close(pd_F_P[0]); //chiudo la pipe in ingresso
	write(pd_F_P[1], &occ, sizeof(int));
	exit(0);
}

int main(){
	int fd;
	int lung_file, num_elementi;
	int pd_P_F18[2], pd_P_F30[2], pd_F18_P[2], pd_F30_P[2]; // pipe descriptors
	int pid; // process id
	int pid_child; //process id del figlio
	int i, occ_18, occ_30, status, figlio, voto;
	int tappo=0;
	char nome_file[]="voti";
	int voti[]={20, 30, 23, 28, 30, 18};
	scrivi_voti(nome_file, voti, 6);
	
	// creo le pipe
	if(pipe(pd_P_F18)==-1){
		printf("Errore nella creazone della pipe\n");
		exit(1);
	}
	if(pipe(pd_F18_P)==-1){
		printf("Errore nella creazone della pipe\n");
		exit(1);
	}	
	if(pipe(pd_P_F30)==-1){
		printf("Errore nella creazone della pipe\n");
		exit(1);
	}
	if(pipe(pd_F30_P)==-1){
		printf("Errore nella creazone della pipe\n");
		exit(1);
	}
	// creo i figli
	pid=fork(); // creo il figlio F18
	if(pid==-1){ printf("Errore nella fork\n"); exit(1);}
	else if(pid==0) // sono il figlio F18
		codice_figlio(pd_P_F18, pd_F18_P, 18);
	else if(pid>0){//sono il padre e genero il figlio 30
		pid=fork(); // creo il figlio F30
		if(pid==-1){ printf("Errore nella fork\n"); exit(1);}
		else if(pid==0) // sono il figlio F30
			codice_figlio(pd_P_F30, pd_F30_P, 30);	
	}
	
	if(pid>0){//sono il padre
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
		// rimetto la testina del file all'inizio
		lseek(fd, 0, SEEK_SET);
		for(i=0; i<num_elementi;i++){
			read(fd, &voto, sizeof(int));
			if(voto==18){
				write(pd_P_F18[1], &voto, sizeof(int));
				printf("P: 18\n");
			}
			else if(voto==30){
				write(pd_P_F30[1], &voto, sizeof(int));
				printf("P: 30\n");
			}
		}
		write(pd_P_F18[1], &tappo, sizeof(int));
		write(pd_P_F30[1], &tappo, sizeof(int));
		close(fd);
		//aspetto che i figni terminino
		pid_child=wait(&status);
		printf("P: Il figlio %d ha terminato l'esecuzione\n", pid_child);
		pid_child=wait(&status);
		printf("P: Il figlio %d ha terminato l'esecuzione\n",pid_child);
		// leggo dalla pipe i conteggi dei figli
		read(pd_F18_P[0], &occ_18, sizeof(int));
		read(pd_F30_P[0], &occ_30, sizeof(int));	
		printf("P: Num occorrenze voto 18 = %d, num occorrenze voto 30 = %d\n", occ_18, occ_30);
	}
	return 0;
}
