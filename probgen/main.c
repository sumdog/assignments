#include "probnstat.h"
#include <stdio.h>
#include <unistd.h>


void usage(){
  printf("\nProbability and Statistics 3470 Statistical Generator\n
Usage: probgen [-r] repetitions [-s] samplesize [-c]
\nsamplesize and repetitions must be integers greater than 0
-c runs the convergence test before preceding
\nGenerates Information for W^2 values of a Chi Squared Distribution
with 1 degree of freedom based on the study by Spinelli and Stephens.\n\n");
}


int main(int argc, char* argv[]){

  //establish some variables
  int sample = 0, rep = 0, ch = 0, x = 0, converge = 0;

  //establish a random seed
  setRandomSeed();

  //parse command line arguments
  while( (ch = getopt(argc, argv, "s:r:c")) != -1){
    switch(ch){
      case 'r': {
	rep = atoi(optarg);
	break;
      }
      case 's': {
	sample = atoi(optarg);
	break;
      }
      case 'c': {
	converge = 1;
	break;
      }
    }//end switch
  }//end whileX
  
  //check args 
  if(rep <= 0 || sample <= 0){
    usage();
    exit(2);
  }

  //begin calculations

  //test to make sure our random generator is making numbers that
  //converge to mu
  if(converge == 1){
    printf("\nTesting Distribution for convergence with Mu=1: \n");
    printf("15:   %lf\n",convergenceTest(1,15));
    printf("50:   %lf\n",convergenceTest(1,50));
    printf("100:  %lf\n",convergenceTest(1,100));
    printf("500:  %lf\n",convergenceTest(1,500));
    printf("1000: %lf\n",convergenceTest(1,1000));
  }

  //setup counter for CV
  int count = 0;
  
  //test sample size with rep number of repititions
  for(x=0; x<rep; x++){
    double *ch1 = generateRandomChiSquareOne(sample);
    sortDoubles(ch1,sample);
    double average = getAverage(ch1,sample);
    double bhat = getBHat(sample,average,*(&ch1[0]));
    double ahat = getAHat(sample,*(&ch1[0]),bhat);
    double *w = getW(ch1,sample,ahat,bhat);
    double *z = getZ(ch1,w,sample);
    double w2 = getWSquared(ch1,z,sample);
    
    if(w2 > .142) {
      count++;
    }
  }

  //setup simulated power
  double power = count/rep;

  //print output
  

}//end main()
