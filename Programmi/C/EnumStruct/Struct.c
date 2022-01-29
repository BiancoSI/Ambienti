#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	float x, y;
	} Punto;
typedef struct {
	Punto centro;
	float raggio;
	} Cerchio;
	
	
float distanza(Punto , Punto);
float Area(Cerchio);

int main(){
		Punto c;
		Cerchio cer;
		printf("X=");
		scanf("%f", &c.x);
		printf("Y=");
        scanf("%f", &c.y);
        printf("Raggio>>");
        scanf("%f", &cer.raggio);
		cer.centro=c;
        printf("Area cerchio : %.3f ", Area(cer) );

        Punto p1;
        p1.x=2;
        p1.y=1;
        Punto p2;
        p2.x=4;
        p2.y=3;
        printf("Distanza tra (%.3f, %.3f) e (%.3f, %.3f) = %.3f\n",p1.x, p1.y, p2.x, p2.y, distanza(p1, p2) );
        return 0;
}

float distanza(Punto p1, Punto p2){
        float dx=p2.x -p1.x;
        float dy=p2.y-p1.y;
        return sqrt(dx*dx + dy*dy);
}
float Area(Cerchio c){
        return (3.1415*c.raggio*c.raggio);
}

