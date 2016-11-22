#ifndef BRUTE_FORCE_MATRIX_C
#define BRUTE_FORCE_MATRIX_C

#include "includes.h"

int THREAD_COUNT = 1;

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
  threadCount++; // because zero indexing is for nerds

  printf("Elapsed time with %d threads: %ld seconds. ", threadCount, timer_elapsed());

  if(threadCount > 1) {
    /* prints either 'No errors occured.' or 'Errors occured.' */
    printf( "%srrors occured.", (!checkErrors() ? "No e" : "E"));
  } else {
    computeParityAmounts();
  }

  printf("\n");
}

void* thread_runner(void* param) {
  int threadNo = (int) param;

  int start = (threadNo * N) / THREAD_COUNT;
  int end = ((threadNo + 1) * N) / THREAD_COUNT;

  int i, j, k;

  for(i = start; i < end; i++) {

    for(j = 0; j < P; j++) {
      C[i][j] = 0;

      for(k = 0; k < M; k++) {
        C[i][j] = A[i][k] * B[k][j];
      }
    }
  }
}

/*
  Given an amount [0-5] the proper function to compute matrix C will
  be called.
*/
void thread_calc(int threadCount) {
  THREAD_COUNT = threadCount + 1;

  pthread_t *threadArr = malloc(THREAD_COUNT * sizeof(pthread_t));
	pthread_attr_t *threadAttrArr = malloc(THREAD_COUNT * sizeof(pthread_attr_t));

	int i;
	for(i = 0; i < THREAD_COUNT; i++){
		pthread_attr_init(&threadAttrArr[i]);
		pthread_create(&threadArr[i], &threadAttrArr[i], thread_runner, (void*) i);
	}

  for (i = 0; i < THREAD_COUNT; i++) {
		pthread_join(threadArr[i], NULL);
	}
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
