#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifndef COUNT_H
#define COUNT_H

#include <stdio.h>
#define BUFFER_SIZE 1024

typedef struct countstruct {
  unsigned long characters;
  unsigned long words;
  unsigned long lines;
} count_t;

count_t* parseFile(FILE *fd);

#endif /* COUNT_H */
