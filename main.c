#ifndef MAIN_C
#define MAIN_C

#include "includes.h"

int main(int argc, char** argv) {
  int i;

  init();

  for(i = 0; i < 6; i++) {
    timer_reset();
    thread_calc(i); /* calculate matrix with i amount of threads */
    printStats(i); /* print statistics about calculation */
  }

  return 0;
}

#endif /* MAIN_C */
