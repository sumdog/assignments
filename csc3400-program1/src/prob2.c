/**\file prob2.c
 *Contains function to solve problem two
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "prob2.h"

/** \fn p2sales()
 *This function will take in user input
 *and create a table to calculate sales total for
 *4 salesmen and 5 products
 */
void p2sales() {
  //input buffer
  char buf[10];
  //storage for sales data
  double sales[4][5];
  //storage for token
  char *token;
  //counters
  unsigned long i,j;

  //init array
  for(i=0;i<4;i++) {
    for(j=0;j<5;j++) {
      sales[i][j]=0;
    }
  }
  
  //instructions for user in interactive mode
  if(isatty(fileno(stdin))) {
    printf("\nEnter data in this format:");
    printf("\n<sales-person>:<product>:<price>");
    printf("\n(1-4):(1-5):9999.99");
    printf("\nUse EOF (^D) to exit\n");
  }

  //input loop
  while( fgets(buf,10,stdin) != NULL ) {
    token = strtok(buf,":\n");
    short count = 3;
    //validation and storage flags
    double v1=-1, v2=-1, v3=-1;
    while( count > 0  ) {
      //convert token to number
      double num = atof(token);
      switch(count) {
      case 3:
	if(num < 1 || num > 4) {
	  fprintf(stderr,"Warning: Invalid salesman\n");
	}
	else {
	  v1=num;
	}
	break;
      case 2:
	if(num <1 || num > 5) {
	  fprintf(stderr,"Warning: Invalid Item\n");
	}
	else {
	  v2=num;
	}
	break;
      case 1:
	if(num < 0) {
	  fprintf(stderr,"Warning: Invalid Price\n");
	}
	else {
	  v3=num;
	}
	break;
      default:
	fprintf(stderr,"Warning: invalid token\n");
      }
      count--;
      token = strtok(NULL,":\n");
    }//end token loop
    
    //if elements are valid, add them to array
    if( v1 > -1 && v2 > -1 && v3 > -1 ) {
      sales[(short)v1-1][(short)v2-1] = sales[(short)v1-1][(short)v2-1] + v3;
    }
  }//end input loop

  //totals
  double ts[4] = { 0,0,0,0 };
  double tp[5] = { 0,0,0,0,0 };

  printf("\nProducts\t\t1\t\t2\t\t3\t\t4\t\t5\ttotal");
  for(i=0; i<4; i++) { //outer salesmen loop
    printf("\nSalesman %d:\t", i+1 ) ;
    for(j=0; j<5; j++) { //inner product loop
      printf("%lf\t",sales[i][j]);
      //totals
      ts[i] += sales[i][j];
      tp[j] += sales[i][j];
      //end of this row, print total
      if(j==4) {
	printf("%lf",ts[i]);
      }
    }
  }
  printf("\nTotals:\t\t%lf\t%lf\t%lf\t%lf\t%lf\n",tp[0],tp[1],tp[2],tp[3],tp[4]);
  printf("\n");
}//end function
