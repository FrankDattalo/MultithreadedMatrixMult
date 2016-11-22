#ifndef BRUTE_FORCE_MATRIX_C
#define BRUTE_FORCE_MATRIX_C

#include "includes.h"

struct threadParams {
  int threadNo;
  int totalThreads;
};

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
    printf( "%srrors occured.", (!checkErrors() ? "No e" : "E"));
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

void* thread_runner(void* params) {
  struct threadParams tParams = (threadParams*) params;
  int threadNo = tParams->threadNo;
  int totalThreads = tParams->totalThreads;

}

static void aInit() {
  int i;
  for(i = 0; i < N; i++) {
    int j;
    for(j = 0; j < M; j++) {
      A[i][j] = i + j;
    }
  }
}

static void bInit() {
  int i;
  for(i = 0; i < M; i++) {
    int j;
    for(j = 0; j < P; j++) {
      B[i][j] = j;
    }
  }
}

void init() {
  aInit();
  bInit();
  timer_reset();
}

#endif /* BRUTE_FORCE_MATRIX_C */
