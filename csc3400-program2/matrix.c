#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

matrix_t* createMatrix(char *name, unsigned short rows, unsigned short cols) {

  unsigned short x;
  double **i;

  //set our struct
  matrix_t *m = malloc(sizeof(matrix_t));
  m->name = malloc(sizeof(char)*strlen(name));
  strcpy(m->name,name);
  m->rows = rows;
  m->cols = cols;
  m->matrix = malloc(sizeof(double*)*cols);

  //alocate memory for each columu
  for(x=0,i=(m->matrix) ; x<rows ; x++, i++) {
    *i = malloc(sizeof(double)*rows);
  }

  //send caller the memory allocated struct
  return m;
}


void fillMatrix(matrix_t *matrix) {
  
  //loop variables and buffer
  char buf[BUFSIZE];
  double **i, *j;
  unsigned short x,y;

  printf("\nPlease enter values for Matrix: %s\n",matrix->name);

  for(x=0,i=matrix->matrix; x < matrix->cols; x++,i++) {
    for(y=0,j=*i; y < matrix->rows; y++, j++) {
      printf("Col: %d, Row: %d\n",x+1,y+1);
      fgets(buf,BUFSIZE,stdin);
      *j = atof(buf);
    }
  }
}

void printMatrix(matrix_t *matrix) {

  double **i, *j;
  unsigned short x,y;

  printf("\nMatrix: %s\n",matrix->name);

  for(x=0,i=matrix->matrix; x < matrix->cols; x++,i++) {
    for(y=0,j=*i; y < matrix->rows; y++, j++) {
      printf("%lf\t",*j);
    }
    printf("\n");
  }
}

void deleteMatrix(matrix_t *matrix) {

  double **m;
  unsigned short x;

  //free memory from each column
  for(x=0, m=matrix->matrix; x < matrix->cols; x++,m++) {
    free( *m );
  }
  //free everything else
  free(matrix->matrix);
  free(matrix->name);
  free(matrix);
}

