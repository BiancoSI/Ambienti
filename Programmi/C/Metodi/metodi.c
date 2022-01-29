#include <stdio.h>
#include <stdlib.h>

// Sezione di dichiarazione dei metodi
double max(double, double);

void scambia(double *, double *);

void raddoppia(double *, int);

int main(){
    double *v;
    int length, i;
    //double m1, m2;
    //Max
    /*double ris;
    printf("Mi dai il valoro di M1>>");
    scanf("%lf", &m1);
    printf("Mi dai il valoro di M2>>");
    scanf("%lf", &m2);
    ris=max(m1, m2);
    printf("Il massimo tra %.3lf e %.3lf è %.3lf .\n",m1, m2 , ris); */
    
    //Scambia
    /*
    printf("Mi dai il valore di M1>>");
    scanf("%lf", &m1);
    printf("Mi dai il valore di M2>>");
    scanf("%lf", &m2);
    printf("In M1--> %.3lf M2---> %.3lf\n",m1, m2);
    scambia(&m1, &m2);
    printf("Scambio di M1 e M2.\nIn M1--> %.3lf ; M2---> %.3lf ;\n",m1, m2);
    */
    printf("Mi dai la lunghezza di v>>");
    scanf("%d", &length);
    v=(double *)malloc(length*sizeof(double));
    if( v==NULL ){
        printf("Oi v è null scusame\n");
        return 1;
    }
    for (i=0; i<length; i++){
        printf("v[%d]>>", i);
        scanf("%lf", &v[i]);
    }
    
    printf("v >> [ ");
    for (i=0; i<length; i++){
        printf(" %.3lf", v[i]);
    }
    printf("]\n");
    raddoppia(v, length);
    printf("v >> [ ");
    for (i=0; i<length; i++){
        printf(" %.3lf", v[i]);
    }
    printf("]\n");
    free(v);
    return 0;
}


// implementazione metodi.

double max( double a, double b){
    return (a>b)? a: b;
}

void scambia(double *pa , double *pb){
    double tmp=*pa;
    *pa=*pb;
    *pb=tmp;
}

void raddoppia(double *v, int dim){
    int i;
    for (i=0; i<dim; i++){
        v[i]=v[i]*2;
    }
}
