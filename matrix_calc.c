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
	pthread_t *threadArr = malloc(threadCount * sizeof(pthread_t));
	pthread_attr_t *threadAttrArr = malloc(threadCount * sizeof(pthread_attr_t));

	int i;
	for(i = 0; i < threadCount; i++){
		pthread_attr_init(&threadAttrArr[i]);

		threadParams params;
		params.threadNo = i;
		params.totalThreads = threadCount;

		pthread_create(&threadArr[i], &threadAttrArr[i], threadRunner, (void*) &params);
	}

  // TODO: ill dangle my pointer for you baby
	int j;
	for (j = 0; j < threadCount; j++) {
		pthread_join (thread[j], NULL);
	}
}

void* thread_runner(void* params) {
  
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
