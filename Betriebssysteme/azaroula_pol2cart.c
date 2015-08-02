# include <stdio.h>
# include <stdlib.h>
# include <math.h>


double* pol2cart (double r, double phi, double x, double y){
 	double* funk_ptr;
 	x=r*cos(phi); 
 	y=r*sin(phi); 

 	funk_ptr = malloc(2*sizeof(double));
 	funk_ptr[0]= x;
 	funk_ptr[1]= y;

  	return funk_ptr;
}


int main(void){
 	double radius;
 	double x;
 	double y;
 	double* ptr;
 
 	printf("radius:");
 	scanf("%lg",&radius); 
 	ptr = pol2cart(radius, M_PI/4, x, y);

 	printf("x=%g\ny=%g\n",*ptr,*(ptr+1));
 
 return 0;
}

