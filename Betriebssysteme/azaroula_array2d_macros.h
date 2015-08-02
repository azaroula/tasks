#ifndef _ARRAY2D_MACROS_H_
#define _ARRAY2D_MACROS_H_
#define ALLOC_ARRAY2D(ARRAY,TYPE,DIM1,DIM2,INIT){ \
 	int i,j; \
 	(ARRAY) = malloc( (DIM1)*sizeof(TYPE*) ); \
 	for(i=0; i< (DIM1); i++) \
		 (ARRAY)[i] = malloc( (DIM2)*sizeof(TYPE) ); \
 	for(i=0; i< (DIM1); i++){ \
	 	for(j=0; j< (DIM2); j++) \
		 	(ARRAY)[i][j]= (INIT); \
	} \
}

#define DELL_ARRAY2D(ARRAY,DIM1){ \
	int i; \
 	for(i=0; i< (DIM1); i++) \
 		free(ARRAY[i]); \
 	free(ARRAY);\
} 
#endif


