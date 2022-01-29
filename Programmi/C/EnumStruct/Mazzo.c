#include <stdio.h>
#include <stdlib.h>
#define CARTE 52
#define PERSEME 13
#define SEMI 4
typedef enum {quadri , cuori, picche, fiori} seme;
typedef struct {
	seme s;
	int val;
} Carta;
int main (){
	int i;
	char semi[]={"quadri", "cuori", "picche", "fiori"};
	Carta *mazzo=(Carta *)malloc(sizeof(Carta)*CARTE);
	for ( i=0; i<CARTE; i++){
		mazzo[i].s=(i/PERSEME)%SEMI;
		mazzo[i].val=i%PERSEME;
	}
	for (i=0; i<CARTE; i++){
		printf ("%d di %s\n", mazzo[i].val, semi[ mazzo[i].s ]);
	}
	free(m);
	return 0;
	

}
