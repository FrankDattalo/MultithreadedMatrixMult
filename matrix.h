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

/* parity amounts */
int cZeroZero;
int cNMinusOneZero;
int cZeroPMinusOne;
int cNMinusOnePMinusOne;

#endif /* MATRIX_H */
