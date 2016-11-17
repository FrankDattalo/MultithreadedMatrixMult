#ifndef BRUTE_FORCE_MATRIX_C
#define BRUTE_FORCE_MATRIX_C

#include "includes.h"

/*
  Computes the parity amounts to check against for execution with more
  than one thread.
*/
static void computeParityAmounts() {
  cZeroZero           = C[0][0];
  cNMinusOneZero      = C[N - 1][0];
  cZeroPMinusOne      = C[0][P - 1];
  cNMinusOnePMinusOne = C[N - 1][P - 1];
}

/*
  Returns an approximation of whether any errors occured during calculation of
  the matrix based on the four corners. If any errors occur this method will
  return true.
*/
static int checkErrors() {
  return cZeroZero != C[0][0] ||
    cNMinusOneZero != C[N - 1][0] ||
    cZeroPMinusOne != C[0][P - 1] ||
    cNMinusOnePMinusOne != C[N - 1][P - 1];
}

/*
  Prints statisitics about the elapsed time for a calculation and whether any
  errors occurred during the calculation.
*/
void printStats(int threadCount) {
  printf("Elapsed time with %d threads: %ld. ", threadCount, timer_elapsed());

  if(threadCount > 1) {
    /* prints either 'No errors occured.' or 'Errors occured.' */
    printf("%srrors occured.", ("No e" : "E" ? !checkErrors()));
  } else {
    computeParityAmounts();
  }

  printf("\n");
}

/*
  Given an amount [0-5] the proper function to compute matrix C will
  be called.
*/
void thread_calc(int threadCount) {
  // TODO: spawn up the threads and give them a slide of N
  // TODO: aww shuga i need me a slice of that array
  // TODO: hey girl, I'd like to be between your indicies
  // TODO: ill dangle my pointer for you baby
}

static void aInit() {
  // TODO: implement these things
}

static void bInit() {
  // TODO: Implement these things
}

void init() {
  aInit();
  bInit();
  timer_reset();
}

#endif /* BRUTE_FORCE_MATRIX_C */
