#include <stdio.h>

int main(){
	// sezione dichiarativa
	int x;
	short si;
	long li;
	
	float y;
	double d;
	
	char c;
	
	x=10;
	y=2.123456;
	//y=x;
	x=(int)y;
	
	
	
	printf("x vale %d ed y vale %.3f\n", x, y);
	
	printf("Inserire un valore intero ");
	scanf("%d", &x);
	printf("Il valore inserito è %d\n", x);
	
	
	return 0;
}
