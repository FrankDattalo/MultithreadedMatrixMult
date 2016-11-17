#ifndef MAIN_C
#define MAIN_C

#include "includes.h"

/*
  Prints statisitics about the elapsed time for a calculation and whether any
  errors occurred during the calculation.
*/
void printStats(int threadCount) {
  printf("Elapsed time with %d threads: %ld. ", threadCount, timer_elapsed());

  if(threadCount > 1) {
    /* prints either 'No errors occured.' or 'Errors occured.' */
    printf("%srrors occured.", ("No e" : "E" ? !checkErrors()));
  }

  printf("\n");
}

int main(int argc, char** argv) {
  int i;

  for(int i = 1; i <= 6; i++) {
    timer_reset(); /* reset timer to current time */
    thread_calc(i); /* calculate matrix with i amount of threads */
    printStats(i); /* print statistics about calculation */

    if (i == 1) {
      computeParityAmounts(); /* if using 1 thread, calculate parity amounts */
    }
  }

  return 0;
}

#endif /* MAIN_C */
