#include <stdio.h>
#include <string.h>

int main (void){

	int i,j;
	char *text;

	printf("Bitte geben sie einen Text ein:");
	scanf("%[^\\]",text);
	printf("Ausgabe:");

	for(i=0; text[i] !='\0'; i++) { 
		switch(text[i]) {
			case '\t': break;
			case '\n': break;
			case ' ' : break; 
			default:
				printf("%c",text[i]);
		}
	}
	printf("\n");
	return 0;
}
