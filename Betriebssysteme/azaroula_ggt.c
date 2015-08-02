#include <stdio.h>
#include <string.h>

int ggt (int m, int n){
	if (m < n)
 		return (ggt(n,m));
 	else if (n == 0)
 		return m;
 	else return 
		(ggt(n,m%n));
}


int main (int argc, char *argv[]){
	int a = atoi(argv[1]);
  	int b = atoi(argv[2]);
 	
 	printf("\tggt(%d,%d) = %d\n",a,b,ggt(a,b));

	return 0; 
}
