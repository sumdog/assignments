typedef struct matrix {
  unsigned short rows;
  unsigned short cols;
  double **matrix;
} matrix;

void createMatrix(unsigned short rows, unsigned short cols);
