#ifndef BRUTE_FORCE_MATRIX_C
#define BRUTE_FORCE_MATRIX_C

#include "includes.h"

/* forward declarations of methods */
void one_thread_calc();
void two_thread_calc();
void three_thread_calc();
void four_thread_calc();
void five_thread_calc();

/*
  Computes the parity amounts to check against for execution with more
  than one thread.
*/
void computeParityAmounts() {
  cZeroZero           = C[0]    [0];
  cNMinusOneZero      = C[N - 1][0];
  cZeroPMinusOne      = C[0]    [P - 1];
  cNMinusOnePMinusOne = C[N - 1][P - 1];
}

/*
  Returns an approximation of whether any errors occured during calculation of
  the matrix based on the four corners. If any errors occur this method will
  return true.
*/
int checkErrors() {
  return cZeroZero != C[0][0] ||
    cNMinusOneZero != C[N - 1][0] ||
    cZeroPMinusOne != C[0][P - 1] ||
    cNMinusOnePMinusOne != C[N - 1][P - 1];
}

/*
  Given an amount [1-6] the proper function to compute matrix C will
  be called.
*/
void thread_calc(int threadCount) {
  switch (threadCount) {
    case 1:
      one_thread_calc();
      break;
    case 2:
      two_thread_calc();
      break;
    case 3:
      three_thread_calc();
      break;
    case 4:
      four_thread_calc();
      break;
    case 5:
      five_thread_calc();
      break;
    case 6:
      six_thread_calc();
      break;
    default:
      printf("THIS SHOULD NOT HAPPEN! THREAD CALC = %d. EXITING!\n", threadCount);
      exit(1);
  }
}

/*
  computes C with one thread.
 */
void one_thread_calc() {
    int i;
    for(i = 0; i < N; i++) {
      int j;
      for(j = 0; j < P; j++) {
        C[i][j] = 0;

        int k;
        for(k = 0; i < M; k++) {
          C[i][j] = A[i][k] * B[k][j];
        }

        // printf("C[%d][%d] = %d\n", N, P, C[N][P]);
      }
    }
}

void two_thread_calc() {
  // TODO: implement
  printf("Not yet implemented");
  exit(1);
}

void three_thread_calc() {
  // TODO: implement
  printf("Not yet implemented");
  exit(1);
}

void four_thread_calc() {
  // TODO: implement
  printf("Not yet implemented");
  exit(1);
}

void five_thread_calc() {
  // TODO: implement
  printf("Not yet implemented");
  exit(1);
}

void six_thread_calc() {
  // TODO: implement
  printf("Not yet implemented");
  exit(1);
}

#endif /* BRUTE_FORCE_MATRIX_C */
