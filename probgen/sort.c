#include "sort.h"
#include <stdlib.h>

void sortDoubles(double* d, int size){
	qsort( d, size, sizeof(double), compare_doubles );
}

int compare_doubles (const void *a, const void *b)
{
	const double *da = (const double *) a;
	const double *db = (const double *) b;
	return (*da > *db) - (*da < *db);
}


