#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "probnstat.h"
#include "sort.h"

double* generateRandomChiSquareOne(int samplesize){
  
  //create our array and pointer
  double *random = malloc(samplesize*sizeof(double));
  double *pa = random;
  //var for loop
  int x;
  //loop through array and assign random chi-squares
  for(x=0; x < samplesize; x++,pa++){
    *pa = randomChiSquareOne();
  }
  //return pointer to array of random doubles
  return random;
}

void setRandomSeed(){
  srand48(time(0) + getpid());
}

double* generateRandomNumber(){
  double *temp = malloc(sizeof(double));
  *temp = drand48();
  return temp;
}

double getAverage(double* list, int size){
  //sum of values
  double sum = 0;
  //loop through and sum values together
  int x;
  for(x=0; x < size; x++, list++)
    { sum = sum + *list; }
  //dive sum by total and return
  return (sum / size);
}

double getBHat(int samplesize, double avg, double element1){
  return ( samplesize*(avg - element1)/(samplesize - 1)  );
}

double getAHat(int samplesize, double element1, double bhat){
  return element1 - (bhat/samplesize);
}

double* getW(double* data, int size, double ahat, double bhat){
  
  //create an array to pass back and a pointer
  double *retval = malloc(size*sizeof(double));
  double *r = retval;
  //looping vars
  int x;
  //calculate w for each item in data set
  for(x=0;x<size;x++,r++,data++){
    *r = (*data - ahat)/bhat;
  }	
  //return array of w values
  return retval;
}

double* getZ(double* data, double* w, int size){
  //create an array to pass back and pointer
  double *retval = malloc(size*sizeof(double));
  double *r = retval;
  
  //calcualte z for each data element
  int x;
  for(x=0; x<size; x++, r++, data++, w++){
    *r = 1 - exp(-*w);
  }
  
  //return array of z values
  return retval;	
}

double getWSquared(double* data, double* z, int size){
  //looping variables
  int x;
  double sum=0;
  //loop
  for(x=0;x<size;x++,data++,z++){
     sum = sum + (*z - ( (2 * *data -1)/(2*size) )  );
  }
  //return W Squared
  return sum + (1/(12*size)) ;
}


double randomNormal(double mu, double sigma) {
  //initalize variables
  double u1, u2, v1, v2, x, c, s;
  s = 2;
  //loop
  while(s > 1){
    u1 = *generateRandomNumber();
    u2 = *generateRandomNumber();
    v1 = 2*u1-1;
    v2 = 2*u2-1;
    s = (v1*v1) + (v2*v2);
  }
  //set c
  c = sqrt( (-2*log(s))/s );
  //return value
  return( sqrt(sigma)*c*v1+mu);  
}

double randomChiSquareOne() {
  return pow( randomNormal(0,1),2 );
}

double convergenceTest(double mu, int reps){
  //initalize variables for holding sum and looping
  double sum = 0;
  int x;
  //sum random values up ChiSquare
  for(x=0;x <reps;x++){
    sum = sum + randomChiSquareOne();
  }
  //return average
  return sum/reps;
}


