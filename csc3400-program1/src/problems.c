#include "problems.h"
#include "prob1.h"
/**\def MAX_ONE
 *maximum input value for problem one
 */
#define MAX_ONE 100 

void runProblemOne() {

  p1DataSet *data = p1createSet(MAX_ONE);
  p1populateSet(data);
  p1printElements(data);
  p1deleteSet(data);

}
