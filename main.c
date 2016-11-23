#ifndef MAIN_C
#define MAIN_C

#include "includes.h"

int main(int argc, char** argv) {
  int i, max;

  init();

  if(argc < 2) {
    fprintf(stderr, "Please enter a number of threads to run the program\n");
    exit(1);
  }

  max = atoi(argv[1]);

  if(max == 0) {
    fprintf(stderr, "Thread count must be a number greater than zero\n");
    exit(2);
  }

  printf("Calculating with %d threads\n", max);

  for(i = 0; i < max; i++) {
    timer_reset();
    thread_calc(i); /* calculate matrix with i amount of threads */
    printStats(i); /* print statistics about calculation */
  }

  return 0;
}

#endif /* MAIN_C */
