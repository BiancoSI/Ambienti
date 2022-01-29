/* soluzione esercizio 3 Nuova traccia N.1 2019,
Realizzare un programma C che, utilizzando le System Call di Linux, conti le occorrenze del carattere ‘a’ nel file “lettera.txt”, contenente L caratteri, (si supponga L multiplo di 2).
Il processo principale dovrà creare una (o più) pipe e quindi 2 processi figli F1, F2. Il primo figlio conterà le occorrenze nella porzione di file dalla posizione 0 alla posizione L/2 – 1 e il secondo dalla posizione L/2 alla posizione L-1. Quindi i figli invieranno al padre i risultati parziali tramite la pipe e il genitore provvederà a calcolare il totale e stamperà in output: Il carattere a è presente n volte nel File Lettera.txt.
(Suggerimento: utilizzare lseek nel caso del secondo figlio per spostarsi di L/2 posizioni nel file.)
Sarà apprezzata la generalizzazione del problema a N figli, con L multiplo di N.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>


#define NUMFIGLI 3
void figlio( int pipedesc[], int inizio, int fine)

    {
          int i, occorrenze =0, fd;
	  char lettera;
          close (pipedesc[0]);
          fd = open("lettera.txt",O_RDONLY);

          lseek (fd,inizio,SEEK_SET);
	   /* ogni figlio calcola la somma parziale e la ritorna al padre */
		for (i=inizio;i<=fine;i++)
		 {
      	    read (fd, &lettera, 1);
		    if (lettera=='a')
		       occorrenze++;
                   }
	  close(fd);
	  write (pipedesc[1], &occorrenze, sizeof(int));
	  exit(0);
         }

int main(int argc, char *argv[])

  {
     int i,pid,pidchild, pipedesc[2],fd,occtot=0,occ,inizio,fine, lungfile,dimproc, status;
     fd = open("lettera.txt",O_RDONLY);
     if (fd==-1)
	  {printf ("Errore nell'apertura del file lettera.txt\n");exit (1);}
     /* calcolo la lunghezza del file */
     lungfile=lseek(fd, 0, SEEK_END);
     close (fd);
     dimproc=lungfile/NUMFIGLI;
     if (lungfile%NUMFIGLI!=0)
	{printf ("Lung. file non è multipla del numero di figli\n");exit(1);}



if (pipe (pipedesc)==-1)
         {printf (" errore nella creazione della pipe\n");exit (2);}

    pid=10; // pid fittizio maggiore di 0
    for (i=0;i<NUMFIGLI;i++)
      if (pid>0)
        {
      	pid = fork();
        inizio = i*dimproc;fine = (i+1)*dimproc-1;
		if (pid==0)
	    	figlio (pipedesc,inizio,fine);
        }
    printf ("inizia il padre\n");
    /* codice del padre (pid > 0, non gestisco l'errore)*/
    close (pipedesc[1]);
    /* Il padre legge le occorrenze parziali e calcola il totale */
    for (i=0;i<NUMFIGLI;i++)
     	      {
				read (pipedesc[0], &occ, sizeof(int));
                                occtot+=occ;
				pidchild = wait (&status);
				printf ("Il figlio %d ha terminato l'esecuzione\n",pidchild);
		}
     printf ("Sono il padre: la lettera 'a' e' presente %d volte nel file lettera.txt\n",occtot);

   return 0;
 }
