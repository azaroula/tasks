#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		printf("Sie haben kein Jahr angegeben \n");
		return EXIT_FAILURE;
 	}

	int a = atoi (argv[1]);

	if (a%4 == 0){
		if(a%100 == 0){
 			if(a%400 == 0){
       				printf("%s ist  ein Schaltjahr \n",argv[1]);
     			} else 
				printf( "%s ist kein Schaltjahr \n",argv[1]);
   		} else 
			printf  ("%s ist ein Schltjahr \n",argv[1]);
 	} else  
		printf ("%s ist kein Schaltjahr \n",argv[1]);
 
 	return 0;
}


