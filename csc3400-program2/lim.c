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

  char *rend1 = randomWord();
  char *rend2 = randomWord();
  short x,y;

  //  for(x=0; x<LINES; x++) {
    //    for(y=floor((float) rand()
  

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

char* randomWord() {

  short x,wordsize = ceil(MAX_WORD_SIZE * ((float) rand()/RAND_MAX));
  char *w, *word = malloc(sizeof(char)*wordsize);

  for(x=0, w=word; x < wordsize; x++,w++) {
    *w = ((float) rand() / (RAND_MAX / (122-97) + 1)) + 97;
  }

  return word;
}
