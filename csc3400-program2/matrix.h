#define BUFSIZE 256

typedef struct matrix {
  char* name;
  unsigned short rows;
  unsigned short cols;
  double **matrix;
} matrix_t;

matrix_t* createMatrix(char *name, unsigned short rows, unsigned short cols);

void fillMatrix(matrix_t *matrix);

void deleteMatrix(matrix_t *matrix);

void printMatrix(matrix_t *matrix);
