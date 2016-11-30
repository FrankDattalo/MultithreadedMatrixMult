#ifndef INCLUDES_H
#define INCLUDES_H

// Frank Dattalo - dattalo.2@osu.edu
// Alex Turner - turner.1303@osu.edu

// Compile Instructions:
// gcc file.c -lpthread -lrt -O1 -Wall

/* include system files with #include here */
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


#endif /* INCLUDES_H */
#ifndef MATRIX_H
#define MATRIX_H

/* matrix dimensions */
#define N 1600
#define M 2000
#define P 500

/* Input matricies */
int A[N][M];
int B[M][P];

/* Output matrix */
int C[N][P];

/* matrix used to check against errors */
int C_PARITY[N][P];

#endif /* MATRIX_H */
#ifndef TIMER_C
#define TIMER_C

/* static variable to keep track of time between calls */
static struct timespec start;
static struct timespec end;

/* resets timer to STARTing time */
void timer_reset() {
  clock_gettime(CLOCK_MONOTONIC, &start);
}

/* returns the elapsed time since timer was reset. */
double timer_elapsed() {
  clock_gettime(CLOCK_MONOTONIC, &end);
  return (end.tv_sec - start.tv_sec) + ((end.tv_nsec - start.tv_nsec) / 1000000000.0);
}

#endif /* TIMER_C */
#ifndef BRUTE_FORCE_MATRIX_C
#define BRUTE_FORCE_MATRIX_C

#define min(a,b)((a<b)?a:b)

static int THREAD_COUNT = 1;

/*
  Computes the parity amounts to check against for execution with more
  than one thread.
*/
static void computeParityAmounts() {
  int i, j;

  for(i = 0; i < N; i++) {
    for(j = 0; j < P; j++) {
      C_PARITY[i][j] = C[i][j];
    }
  }
}

/*
  Returns an approximation of whether any errors occured during calculation of
  the matrix based on the four corners. If any errors occur this method will
  return true.
*/
static int checkErrors() {

  int i, j;
  int errors = 0;

  for(i = 0; i < N; i++) {
    for(j = 0; j < P; j++) {
      if(C_PARITY[i][j] != C[i][j]) {
        fprintf(stderr, "Error occured on C[%d][%d], expected %d, was %d.\n", i, j, C_PARITY[i][j], C[i][j]);
        errors = 1;
      }
    }
  }

  return errors;
}

/*
  Prints statisitics about the elapsed time for a calculation and whether any
  errors occurred during the calculation.
*/
void printStats(int threadCount) {
  threadCount++;

  printf("Elapsed time with %d threads: %lf seconds. ", threadCount, timer_elapsed());

  if(threadCount > 1) {
    /* prints either 'No errors occured.' or 'Errors occured.' */
    printf( "%srrors occured.", (!checkErrors() ? "No e" : "E"));
  } else {
    computeParityAmounts();
  }

  printf("\n");
}

/* 
  Function that threads run to calculate matrix
*/
static void* thread_runner(void* param) {
  int threadNo = *(int*) param;

  int i, j, k, ii, kk, jj, K_TILE, I_TILE, J_TILE, iend, jend, kend;

  /* loop tile sizes */
  K_TILE = 1024;
  J_TILE = 512;
  I_TILE = 2048;

  /* i > k > j */
  /* min() prevents seg faults here */

  for(ii = threadNo; ii < N; ii += I_TILE) {
    
    for(i = ii, iend = min(N, ii + I_TILE); i < iend; i += threadNo + THREAD_COUNT) {

      for(jj = 0; jj < P; jj += J_TILE) {

        for(j = jj, jend = min(P, jj + J_TILE); j < jend; j++) {
          C[i][j] = 0;

          for(kk = 0; kk < M; kk += K_TILE) {

            for(k = kk, kend = min(M, kk + K_TILE); k < kend; k++) {
              C[i][j] = A[i][k] * B[k][j];
            }
          }
        }
      }
    }
  }

  return NULL;
}

/*
  Calculates c with n threads
*/
void thread_calc(int threadCount) {
  THREAD_COUNT = threadCount + 1;

  pthread_t *threadArr = malloc(THREAD_COUNT * sizeof(pthread_t));
  pthread_attr_t *threadAttrArr = malloc(THREAD_COUNT * sizeof(pthread_attr_t));
  int* indexArr = malloc(THREAD_COUNT * sizeof(int));

  int i;
  for(i = 0; i < THREAD_COUNT; i++){
    indexArr[i] = i;
    pthread_attr_init(&threadAttrArr[i]);
    pthread_create(&threadArr[i], &threadAttrArr[i], thread_runner, &indexArr[i]);
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
}

#endif /* BRUTE_FORCE_MATRIX_C */
#ifndef MAIN_C
#define MAIN_C

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
