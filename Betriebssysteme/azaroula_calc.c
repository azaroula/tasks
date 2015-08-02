#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
	if(argc != 4) {
		printf("Sie haben nicht 3 Arguente angegeben\n");
		return EXIT_FAILURE;
	}
	
	float a = atof(argv[1]);
	float b = atof(argv[3]);

	switch(argv[2][0]){
		case '+': printf("%g\n",a + b);break;
		case '-': printf("%g\n",a - b);break;
		case 'x': printf("%g\n",a * b);break;
		case '/': printf("%g\n",a / b);break;
		default: 
			printf("Ihr Zweiter Parameter entspricht nicht: + - x /\n");
			return EXIT_FAILURE;
	}
		return 0;
}
	
