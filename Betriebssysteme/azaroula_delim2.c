#include <stdio.h>
#include <string.h>
# include <stdlib.h>

int main (void){
	int i, j=0;
	char *in_array, *text;
	
	printf("Bitte geben sie einen Text ein:");
	scanf("%[^\\]",in_array);
	printf("Ausgabe:");	

	for(i=0; in_array[i] != '\0'; i++) { 
		switch(in_array[i]) {
			case '\t': break;
			case '\n': break;
			case ' ' : break; 
			default:
				text[j] = in_array[i];
				j++;
		}
	}
	printf("%s", text);
	printf("\n");
	return 0;
}


