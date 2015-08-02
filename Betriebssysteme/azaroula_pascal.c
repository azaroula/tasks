#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[]) {

	int i = atoi(argv[1]);
	int z,s;
 
	for(s=0; s<i; s++){
		for(z=0; z<=s; z++)
			printf("%d ",binkoeff(z,s));
			printf("\n");
	}	
	return 0; 
}

int binkoeff(int zeile, int spalte) {

	if(zeile == 0 || spalte == zeile)
		return 1; 
	else 
		return(binkoeff(zeile-1,spalte-1) + binkoeff(zeile,spalte-1)); 
}







