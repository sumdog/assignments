/**\file prob1.h
 *This file includes the function and struct definitions 
 *needed to perform problem 1.
 */
#include <stdio.h>
#include <unistd.h>

/**\struct p1DataSet
 * \brief Type used to hold data for Sets a and b
 */
typedef struct p1DataSetStruct {
  long *seta;  ///<Pointer to Integer Set A
  long *setb;  ///<Pointer to Integer Set B
  unsigned short sizea, sizeb; ///<The current size of the set(s)
  unsigned short maxsize;      ///<The Maximum size of the set(s)
} p1DataSet;

/**\struct p1CalSet
 * \brief A struct to hold the calculations from a set operation
 * This struct holds the results from combining to sets that
 * are held in a p1DataSet struct.
 * \see p1DataSet
 */
typedef struct p1CalSetStruct {
  long *set_union;             ///<Union of two sets (A and B)
  unsigned short union_size;   ///<Size of Union
  long *intersection;          ///<Intersection of two sets (A or B)
  unsigned short inter_size;   ///<Size of Intersection
  long *subtract;              ///<Subtraction of two sets (A but not B)
  unsigned short sub_size;     ///<Size of Subtraction
} p1CalSet;

/**\fn p1DataSet* p1createSet(unsigned short max)
 *\brief creates a data set
 *\param max Maximum size of the datasets
 *\return a pointer to a memory allocated dataset
 *\see void p1deleteSet(p1DataSet* set)
 */
p1DataSet* p1createSet(unsigned short max);
/**\fn void p1deleteSet(p1DataSet* set)
 *\brief will free the memory allocated to a dataset pointer
 *\param set a dataset allocated using p1createSet function
 *\see p1DataSet* p1createSet(unsigned short max)
 */
void p1deleteSet(p1DataSet* set);
/** \fn void p1populateSet(p1DataSet *set);
 *  \brief populates data sets with user input
 *  \param data struct with perallocated memory
 */
void p1populateSet(p1DataSet *set);
/** \fn void p1printElements(p1DataSet *data)
 *  \brief prints the data set to standard out
 *  \param data dataset to print
 */
void p1printElements(p1DataSet *data);
/**
 *\fn short p1checkDups(long *set, long check, unsigned short size);
 *\brief checks for duplicates in an array
 *\param set a pointer to a set of interger data
 *\param check the element to check for duplicates of
 *\param size the size of the array allocated to set
 *\return -1 if a duplicate is found, 0 otherwise
 */
short p1checkDups(long *set, long check, unsigned short size);
