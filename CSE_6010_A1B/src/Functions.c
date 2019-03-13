/*
 * Functions.c
 *
 *  Created on: 2018.08.31
 *      Author: CAI
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

//Create a two-dimensional matrix using dynamic memory allocation
double **malloc_matrix(int n1, int n2) {
	double** mat = (double **)malloc(n1 * sizeof(double*));
	int i;
	for (i = 0; i < n1; i++) {
		*(mat + i) = (double *)malloc(n2 * sizeof(double));
		if (*(mat + i) == NULL) {
			printf("Allocation error!\n");
			return NULL;
		}		//if allocation fails, return NULL
	}
	if (mat == NULL)
		printf("Allocation error!\n");
	return mat;		//if allocation fails, return NULL.
}

//Release the memory allocated for the matrix
void free_matrix (int n1, int n2, double **a) {
	int i;
	for (i = 0; i < n1; i++) {
		free(a[i]);
	}
	free(a);
}

//Fill the matrix with random values between 0.0 and 10.0
void fill_matrix(int n1, int n2, double **a) {
	int i, j;

	if (a == NULL) {
		printf("Matrix is NULL!\n");
		return;
	}

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			*(*(a + i) + j) = rand() % 101 * 0.1;
		}
	}
}

//Print the matrix
void print_matrix(int n1, int n2, double **a) {
	int i, j;

	if (a == NULL) {
		printf("Matrix is NULL!\n");
		return;
	}

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n2; j++) {
			printf("%7.2f", *(*(a + i) + j));
		}
		printf("\n");
	}
	printf("\n");
}

//Matrix multiplication between matrix a=n1*n2 and matrix b=n2*n3
int matrix_multiply(int n1, int n2, int n3, double **a, double **b, double **c) {
	int i, j, k;
	double sum = 0;
	if (a == NULL || b == NULL || c == NULL)
		return 0;

	for (i = 0; i < n1; i++) {
		for (j = 0; j < n3; j++) {
			for (k = 0; k < n2; k++) {
				sum += a[i][k] * b[k][j];
			}
			c[i][j] = sum;
			sum = 0;
		}
	}
	return 1;
}


