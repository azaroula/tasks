#include "azaroula_array2d_macros.h"
#include <stdio.h>
#include <stdlib.h>

int 
main (void){

 int i,j,s,z;
 int **matrix;

 printf("wie viele Spalten?:");
 scanf("%d",&s);
 printf("wie viele Zeilen?:");
 scanf("%d",&z);

 ALLOC_ARRAY2D(matrix,int,s,z,2)

 for(i=0; i<s; i++){ 
	 for(j=0; j<z; j++)
		 printf("array[%d][%d]= %d\n",i,j,matrix[i][j]);
 }
 DELL_ARRAY2D(matrix,s)

 return 0;
}
