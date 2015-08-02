#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void auswerten(double zahl, double (*ptr_funktion) (double i)) {
	double i;
 	for (i=0; i<=zahl; i++)
 	printf("| %f = %f |\n",i,(*ptr_funktion) (i) );
}

int main (void) {
 	int w, i;
 	double z;

 	printf("Geben sie eine Zahl ein:");
 	scanf("%lg",&z);

 	printf("\nWelche Operation möchten sie Ausführen?\n");
 	printf("1:sqrt\n2:sin\n3:cos\n4:tan\n:");
 	scanf("%d",&w);
 	switch(w){
        case 1: printf("\nsqrt(<=%g):\n",z); auswerten(z,sqrt); break; 
		case 2: printf("\nsin(<=%g):\n",z); auswerten(z,sin); break;
		case 3: printf("\ncos(<=%g):\n",z); auswerten(z,cos); break;
		case 4: printf("\ntan(<=%g):\n",z); auswerten(z,tan); break;
 	}
	return 0;
}

