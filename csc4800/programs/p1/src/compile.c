/* put necessary includes here */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int compile(char *src, char* out) {
  

  /* create outfile or if it exists
     open it and truncate it to 0 */
  freopen("outfile.txt","w+",stderr);
 
  pid_t child = fork();
  if(child) { /* parent */
    freopen("/dev/tty","a",stderr);
    int state;
    waitpid(child,&state,0);
    return state;
  }
  else { /* child */
    return execl("/usr/bin/gcc","gcc",src,"-o",out,NULL);
  }

  
}
