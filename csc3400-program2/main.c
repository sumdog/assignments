#include "matrix.h"

int main() {
  
  matrix_t *test = createMatrix("Bob",2,4);
  fillMatrix(test);
  printMatrix(test);
  deleteMatrix(test);

}
  

