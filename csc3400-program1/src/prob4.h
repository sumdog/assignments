/**\file prob4.h
 *Function prototypes for problem #4
 */

/**\fn unsigned long p4binary_search(long array[], unsigned long start, unsigned long end, long key)
 *\brief Performed a binary search of a sorted array
 *\param array Integer array to be searched
 *\param start Where to start searching in array
 *\param end Where to end searching in array
 *\param key element to search for
 *\return index of array where element exists or -1 if not found
 */
unsigned long p4binary_search(long array[], unsigned long start, unsigned long end, long key);
