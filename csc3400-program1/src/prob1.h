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
 *\return -1 if duplicate found, 0 otherwise
 */
short p1checkDups(long *set, long check, unsigned short size);

/**
 *\fn p1CalSet* performCalculations(p1DataSet *data)
 *\brief performs set calculations on the dataset
 *\param data dataset to perfrom calculations on
 *\return a struct containing the results of the calculations
 */
p1CalSet* p1performCalculations(p1DataSet *data);


/**
 *\fn void p1destroyCalculations(p1CalSet *data)
 *\brief will free memory allocated to a calculation struct
 *\param data dataset to destory
 */
void p1destroyCalculations(p1CalSet *data);

/**
 *\fn short p1removeElement(long *set, long check, unsigned short size)
 *\breif removes an element from a set
 *\param set the set to remove the element from
 *\param check element to remove
 *\param size the size of the set
 *\return 0 if element was removed, -1 if element wasn't found
 */
short p1removeElement(long *set, long check, unsigned short size);

/**
 *\fn void p1printResults(p1CalSet *result)
 *\breif displays calculations performed on a set
 *\param result struct that contains set calculations
 *\param data struct containing original sets
 */
void p1printResults(p1DataSet *data, p1CalSet *result);
