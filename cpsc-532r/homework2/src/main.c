#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include "count.h"

int main() {

  char *package = PACKAGE;
  char *version = VERSION;
#ifdef HAVE_WC
  char *backend = WC_PATH;
#else
  char *backend = "Internal";
#endif

  if(isatty(fileno(stdin))) {
    printf("%s  %s  Backend:%s\tSumit Khanna\n",package,version,backend);
  }

   count_t *counter = parseFile(stdin);
   printf("Number of Bytes:%d\n",counter->characters);
   printf("Number of Words:%d\n",counter->words);
   printf("Number of Lines:%d\n",counter->lines);
   free(counter);
}
