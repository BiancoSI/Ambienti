#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define F 10

int main(){
		int** pi_pe;
		int i; int pid=1;
		int nf;
		int vinc[2];
		int permesso[2];
		pipe(permesso);
		pipe(vinc);
		pi_pe=(int **)malloc(sizeof(int *)*F);
		for (i=0;i<F; i++){
			pi_pe[i]=(int *)malloc(sizeof(int)*2);
		}
		for (i=0;i<F; i++){
			if (pipe(pi_pe[i])< 0){
				printf("Cazzo....\n Aaaaaah...\n ...A mano\n");
				exit(1);
			}
		}
		for(i=0; i<F && pid>0; i++){
			nf=i;
			pid=fork();
		}
		if ( pid <0 ){
			printf("Creazione Processo Fallita\n");
		}else if (pid == 0){
			int vincitore;
			int offerta;

			read(permesso[0], &i, sizeof(int));
			printf("Il processo %d offre  ", nf);
			scanf("%d", &offerta);
			printf("Il processo %d ha offerto %d\n", nf, offerta);
			close(permesso[0]);
			write(permesso[1], &i, sizeof(int));
			close(permesso[1]);

			close(pi_pe[nf][0]);
			write(pi_pe[nf][1], &offerta, sizeof(int));
			close(pi_pe[nf][1]);

			close(vinc[1]);
			read(vinc[0], &vincitore, sizeof(int));
			close(vinc[0]);

			if ( nf == vincitore){
				printf("%d :Ho vinto\n", nf);
			}else{
				printf("%d :Ho perso\n", nf);
			}
			exit(1);
		}else {
			close(permesso[0]);
			write(permesso[1], &i, sizeof(int));
			close(permesso[0]);

			int offertaVincente;
			int offerte[F];
			int status;
			for(i=0; i<F; i++){
				close(pi_pe[i][1]);
				read(pi_pe[i][0], &offerte[i], sizeof(int));
				close (pi_pe[i][0]);
			}
			printf("Aperto L'appalto Vince € : ");
			scanf("%d", &offertaVincente);
			int v=0;
			int prezzo;
			int dist=offerte[i];
			for (i=0; i<F; i++){
				prezzo = offertaVincente-offerte[i];

				if (prezzo<0 ) prezzo=prezzo*-1;

				if ( dist > prezzo ){
					v=i;
					dist=prezzo;
				}
			}
			close(vinc[0]);
			for(i=0; i<F; i++){
				write(vinc[1], &v, sizeof(int));
			}
			close(vinc[1]);
			for(i=0; i<F; i++){
				wait(&status);
			}
		}
		return 0;
}
