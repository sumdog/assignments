#include "matrix.h"

void createMatrix(unsigned short rows, unsigned short cols) {

  unsigned short x, y;
  double i,j;

  matrix *m = (matrix*) malloc(sizeof(matrix));
  m->rows = rows;
  m->cols = cols;
  m->matrix = (double**) malloc(sizeof(double*)*rows);

  //  for(x=0,i=&(*matrix)[0] ; x<rows ; x++, i++) {

  //}
}
