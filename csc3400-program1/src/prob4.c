/**\file prob4.c
 *This file contains the functions to perform
 *a binary search of a sorted array.
 */


/**\fn unsigned long p4binary_search(long array[], unsigned long start, unsigned long end)
 *Performes a binary search of a sorted long (32-bit) integer array) recursivly
 */
unsigned long p4binary_search(long array[], unsigned long start, unsigned long end, long key) {

  unsigned long mid = start+((end-start)/2);

  //base cases
  if( array[mid] == key ) //element found at mid
    { return mid; }
  //  else if ( array[start] == key) //element right in front of mid
  //  { return start; }
  else if ( array[end] == key)
    { return end; }
  else if (mid == end || mid == start) //no such element
    { return -1; }
  //recursive cases
  if(array[mid] > key) {
    return p4binary_search(array, start, mid-1, key);
  }
  else {
    return p4binary_search(array,mid+1, end, key);
  }

  //failsafe (you should not get here!!!)
  return -2; //something went wrong

}
