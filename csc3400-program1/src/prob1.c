/**\file prob1.c
 *Functions for problem 1
 */
#include "prob1.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**\fn p1DataSet* p1createSet(unsigned short max)
 * This function allocates memory for a data struct that
 * holds two sets of data, each with a maximum capicty max.
 */
p1DataSet* p1createSet(unsigned short max) {
  p1DataSet *data = (p1DataSet*) malloc(sizeof(p1DataSet));
  data->seta = (long*) malloc(sizeof(long)*max);
  data->setb = (long*) malloc(sizeof(long)*max);
  data->sizea = 0;
  data->sizeb = 0;
  data->maxsize = max;

  return data;
}

/**\fn void p1deleteSet(p1DataSet* set)
 *This function deallocates memory previously allocated 
 *for the given dataset struct
 */
void p1deleteSet(p1DataSet* set) {
  free(set->seta);
  free(set->setb);
  free(set);
}

/**\fn void p1populateSet(p1DataSet *set)
 *This will ask the user for input (and prompt them in 
 *interactive mode), check for duplicates and if no duplicates
 *exist, it wil place the user input into the dataset.
 *The user inputs data in the format "<itema>:<itemb>"
 */
void p1populateSet(p1DataSet *set) {
  
  //print instructions if in interactive mode
  if(isatty(fileno(stdin))) {
    printf("\nEnter two numbers in the following format:");
    printf("\n<num a>:<num b>");
    printf("\nexample:");
    printf("\n3:4");
    printf("\nUse end of file (^D) to exit\n");

    }
  
  //setup counters and initial array pointers
  unsigned int count = set->maxsize;
  long *a = &(set->seta[0]);
  long *b = &(set->setb[0]);


  //determine the maximum string length imput size
  //for a long on this operating system/arch
  char buf[256];
  sprintf(buf,"%d",LONG_MAX);
  unsigned long inputsize = strlen(buf);


  //while we haven't reached EOF or the counter is > 0,
  //read in stuff into our buffer
  //(buffer size acomidates 2 inputs plus the '-' between them 
  while( (count != 0) && (fgets(buf,inputsize*2 + 1,stdin)!=NULL) )  {
    char *token = strtok(buf,":\n");
    short count = 2;
    while(token) {
      long curnum = atol(token);
      switch(count) {
      case 2:
	if( p1checkDups(set->seta,curnum,set->sizea) ) {
	  fprintf(stderr,"Duplicate Element in Set A: %d\n",curnum);
	} else {
	  *a = curnum;
	  set->sizea++;
	  a++;
	}
	break;
      case 1:
	if( p1checkDups(set->setb,curnum,set->sizeb) ) {
	  fprintf(stderr,"Duplicate Element in Set B: %d\n",curnum);
	} else {
	  *b = atol(token);
	  set->sizeb++;
	  b++;
	}
	break;
      default:
	fprintf(stderr,"Invalid Element: %d\n",curnum);
      }
      count--;
      token = strtok( NULL, ":\n" );
    }//end per line while loop
  }//end entire input while loop
}//end populateSet Function

/**
 * \fn void p1printElements(p1DataSet *data)
 * This function is mainly a debuging function that 
 * will print out all the elements so the programmer
 * can make sure the datastructer is storing them correctly.
 */
void p1printElements(p1DataSet *data) {
  unsigned short a = data->sizea, b=data->sizeb;
  long *pa = &(data->seta[0]), *pb = &(data->setb[0]);

  printf("A:B\n");

  while( a > 0 || b > 0 ) {
    if(a > 0) {
      printf ("%d", *pa);
      pa++;
      a--;
    }
    printf(" : ");
    if(b > 0) {
      printf("%d", *pb);
      pb++;
      b--;
    }
    printf("\n");
  }//end while
}//end printElements function

/**
 *\fn short p1checkDups(long *set, long check, unsigned short size)
 *This is an internal function used by several of the other functions and 
 *is not designed to be called independently.
 */
short p1checkDups(long *set, long check, unsigned short size) {
  long *x;
  for( x=&set[0]; size > 0; x++, size-- ) {
    if(*x == check) {
      return -1;
    }
  }
  return 0;
}


p1CalSet* performCalculations(p1DataSet *data) {
  //setup our return struct
  p1CalSet *calset = (p1CalSet*) malloc(sizeof(p1CalSet));
  long datasize = data->sizea > data->sizeb ? data->sizea : data->sizeb;
  calset->set_union = (long*) malloc(sizeof(  datasize ));

  //setup some set pointers
  
}
