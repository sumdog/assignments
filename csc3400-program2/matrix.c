#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {

  short a_rows, a_cols, b_rows, b_cols, s_a, s_b;
  char buffer[BUFSIZE];

  printf("Enter number of rows for Matrix a:\n");
  fgets(buffer,BUFSIZE,stdin);
  a_rows = atoi(buffer);

  printf("Enter number of cols for Matrix a:\n");
  fgets(buffer,BUFSIZE,stdin);
  a_cols = atoi(buffer);

  printf("Enter number of rows for Matrix b:\n");
  fgets(buffer,BUFSIZE,stdin);
  b_rows = atoi(buffer);

  printf("Enter number of rows for Matrix b:\n");
  fgets(buffer,BUFSIZE,stdin);
  b_cols = atoi(buffer);

  printf("Enter scalor to multiply a by:\n");
  fgets(buffer,BUFSIZE,stdin);
  s_a = atoi(buffer);

  printf("Enter scalor to multiply b by:\n");
  fgets(buffer,BUFSIZE,stdin);
  s_b = atoi(buffer);

  matrix_t *a = createMatrix("A",a_rows,a_cols);
  fillMatrix(a);

  matrix_t *b = createMatrix("B",a_rows,a_cols);
  fillMatrix(b);
  
  matrix_t *add = addMatrix(a,b);

  matrix_t *sub = subtractMatrix(a,b);

  printMatrix(a);
  printMatrix(b);
  printMatrix(add);
  printMatrix(sub);

  if(equalMatrix(a,b)) {
    printf("\nA and B are equal\n");
  }
  else {
    printf("\nA and B are not equal\n");
  }
  
  scalarMatrix(a,s_a);
  scalarMatrix(b,s_b);
  printMatrix(a);
  printMatrix(b);

}

matrix_t* createMatrix(char *name, unsigned short rows, unsigned short cols) {

  unsigned short x;
  double **i;

  //set our struct
  matrix_t *m = malloc(sizeof(matrix_t));
  m->name = malloc(sizeof(char)*strlen(name));
  strcpy(m->name,name);
  m->rows = rows;
  m->cols = cols;
  m->matrix = malloc(sizeof(double*)*rows);

  //alocate memory for each columu
  for(x=0,i=(m->matrix) ; x<rows ; x++, i++) {
    *i = malloc(sizeof(double)*cols);
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

  for(x=0,i=matrix->matrix; x < matrix->rows; x++,i++) {
    for(y=0,j=*i; y < matrix->cols; y++, j++) {
      printf("Col: %d, Row: %d\n",y+1,x+1);
      fgets(buf,BUFSIZE,stdin);
      *j = atof(buf);
    }
  }
}

void printMatrix(matrix_t *matrix) {

  double **i, *j;
  unsigned short x,y;

  printf("\nMatrix: %s\n",matrix->name);

  for(x=0,i=matrix->matrix; x < matrix->rows; x++,i++) {
    for(y=0,j=*i; y < matrix->cols; y++, j++) {
      printf("%lf\t",*j);
    }
    printf("\n");
  }
}

void deleteMatrix(matrix_t *matrix) {

  double **m;
  unsigned short x;

  //free memory from each column
  for(x=0, m=matrix->matrix; x < matrix->rows; x++,m++) {
    free( *m );
  }
  //free everything else
  free(matrix->matrix);
  free(matrix->name);
  free(matrix);
}

matrix_t*  addMatrix(matrix_t *a, matrix_t *b) {

  //temps
  double **m1, *n1, **m2, *n2, **ret, *re;
  unsigned short x,y;

  //you can only add them if they're equal
  if(a->rows != b->rows && a->cols != b->cols) {
    return NULL;
  }

  //return matrix
  char *name = malloc(sizeof(char)*(strlen(a->name)+strlen(b->name)+3));
  strcpy(name,a->name);
  strcat(name," + ");
  strcat(name,b->name);
  matrix_t *c = createMatrix(name,a->rows,a->cols);
  free(name);

  //add them
  for(m1=a->matrix, m2=b->matrix,x=0,ret=c->matrix; x<a->rows; x++,m1++,m2++,ret++) {
    for(n1=*m1, n2=*m2, re=*ret, y=0; y<a->cols; y++,n1++,n2++,re++) {
      *re = *n1 + * n2;
    }
  }
  return c;
}

matrix_t* subtractMatrix(matrix_t *a, matrix_t *b){
  //temps
  double **m1, *n1, **m2, *n2, **ret, *re;
  unsigned short x,y;

  //you can only add them if they're equal
  if(a->rows != b->rows && a->cols != b->cols) {
    return NULL;
  }

  //return matrix
  char *name = malloc(sizeof(char)*(strlen(a->name)+strlen(b->name)+3));
  strcpy(name,a->name);
  strcat(name," - ");
  strcat(name,b->name);
  matrix_t *c = createMatrix(name,a->rows,a->cols);
  free(name);

  //add them
  for(m1=a->matrix, m2=b->matrix,x=0,ret=c->matrix; x<a->rows; x++,m1++,m2++,ret++) {
    for(n1=*m1, n2=*m2, re=*ret, y=0; y<a->cols; y++,n1++,n2++,re++) {
      *re = *n1 - * n2;
    }
  }
  return c;
}

short equalMatrix(matrix_t *a, matrix_t *b){

  //temps
  double **m1, *n1, **m2, *n2;
  unsigned short x,y;

  //you can only add them if they're equal
  if(a->rows != b->rows && a->cols != b->cols) {
    return 0;
  }

  //add them
  for(m1=a->matrix, m2=b->matrix,x=0; x<a->rows; x++,m1++,m2++) {
    for(n1=*m1, n2=*m2, y=0; y<a->cols; y++,n1++,n2++) {
      if( *n1 != *n2 ){ return 0; }
    }
  }
  return 1;
}


void scalarMatrix(matrix_t *a, double scalar){

  double **i, *j;
  short x,y;

  char *name = malloc(sizeof(char)*(strlen(a->name)+BUFSIZE));
  char temp[BUFSIZE];
  strcpy(name,a->name);
  sprintf(temp," * %lf",scalar);
  strcat(name,temp);
  free(a->name);
  a->name = name;

  for(x=0,i=a->matrix; x < a->rows; x++,i++) {
    for(y=0,j=*i; y < a->cols; y++,j++) {
      *j *= scalar;
    }
  }
}
