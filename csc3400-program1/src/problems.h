/**\file problems.h
 *Prototypes and definitions for testing
 *various problems.
 */

/**\def MAX_ONE
 *maximum input value for problem one
 */
#define MAX_ONE 100 
/**\def ARRAY_FOUR
 *predefined array for problem 4 = {-5 -1 0 12 48 62 102 112}
 */
#define ARRAY_FOUR {-5, -1, 0, 12, 48, 62, 102, 112}
/**\def LENGTH_FOUR
 *length of ARRAY_FOUR
 */
#define LENGTH_FOUR 7 


/**
 *\fn void runProbOne()
 *\brief solves problem one
 */
void runProblemOne();

/**
 *\fn void runProblemSix( double n , short type)
 *\brief solves problem six
 *\param n index of fibonacci number to produce
 *\param type 1 to store data in 32-bit integer, 2 for double
 */
void runProblemSix( double n , short type);

/**\fn short runProblemFive(char *s)
 *\brief solves problem five
 *\param s string to evaluate
 *\return 1 if true, 0 if false
 */
short runProblemFive(char *s);

/**
 *\fn void runProblemTwo()
 *\brief solves problem two
 */
void runProblemTwo();

/**\fn void runProblemThree(char* s1, char* s2)
 *\brief tests to see if problem two works.
 *\param s1 string one (to copy)
 *\param s2 string two (to compare)
 */
void runProblemThree(char* s1, char* s2);

/**\fn void runProblemFour(long element)
 *\brief tests to see if problem four works
 *\param element element to look for
 */
void runProblemFour(long element);
