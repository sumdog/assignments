#include "matrix.h"

int main() {
  
  matrix_t *test = createMatrix("Bob",3,4);
  fillMatrix(test);
  printMatrix(test);
  deleteMatrix(test);

}
  

