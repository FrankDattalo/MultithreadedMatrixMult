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
