#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

char buf[40];
sem_t sem;
void* child(void *arg);

int main() {
  pthread_t thr;
  sem_init(&sem,0,0);
  pthread_create(&thr,NULL,child,NULL);
  sprintf(buf,"Hello World");
  sem_post(&sem);
  pthread_join(thr,NULL);
  printf("%s\n",buf);
  exit(0);
}

void* child(void *arg) {
  sem_wait(&sem);
  strcat(buf,"child: hello\n");
  pthread_exit(0);
}
