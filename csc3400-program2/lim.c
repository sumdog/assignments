#include "lim.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {

  srand(time(0)+getpid());

  char *end1 = randomWord();
  char *end2 = randomWord();
  short x;


  for(x=0; x<=LINES; x++) {
    switch (x) {
    case 1:
    case 2:
    case 5:
      printf("%s %s%s\n",randomLine(),randomWord(),end1);
      break;
    case 3:
    case 4:
      printf("%s %s%s\n",randomLine(),randomWord(),end2);
      break;
    }
  }
  

}

char** getLim(){

  //temp variables
  short lines;
  char line[BUFFER];
  char **ret = malloc(sizeof(char*)*LINES);
  char **temp = ret;
  char *l;

  //loop to get lines
  for(lines=LINES, l=fgets(&line[0],BUFFER,stdin); 
      lines>0 &&  l!=NULL; 
      --lines,l=fgets(&line[0],BUFFER,stdin)) {

    //inner loop to parse through and get last word
    char *t,*word;
    for(t=strtok(&line[0]," "); t != NULL; t=strtok(NULL," ")) {
      word = t;
    }
    *temp = malloc(sizeof(char)*strlen(word));
    strcpy(*temp,word);
    temp++;
    
    if(lines == 1) { break; }

  }

  return ret;
}

//generates a random line
char* randomLine() {
  
  short words = floor(MAX_WORDS_PER_LINE * ((float) rand()/RAND_MAX)),x;
  char *retval = malloc(sizeof(char)*BUFFER);
  strcpy(retval,"");

  for(x=0; x<words; x++) {
    strcat(retval,randomWord());
    strcat(retval," ");
  }
  
  return retval;

}

//generates a random word
char* randomWord() {

  short x,wordsize = ceil(MAX_WORD_SIZE * ((float) rand()/RAND_MAX));
  char *w, *word = malloc(sizeof(char)*wordsize);

  for(x=0, w=word; x < wordsize; x++,w++) {
    *w = ((float) rand() / (RAND_MAX / (122-97) + 1)) + 97;
  }

  return word;
}

