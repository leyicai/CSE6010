#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define MAT_SIZE 50		//size of matrices
#define NUM_THREADS 60

//Global Variables
double A[MAT_SIZE][MAT_SIZE];
double B[MAT_SIZE][MAT_SIZE];
double C[MAT_SIZE][MAT_SIZE];	//result from static mapping
double D[MAT_SIZE][MAT_SIZE];	//result from dynamic mapping
double E[MAT_SIZE][MAT_SIZE];	//result from sequential code

void print (double A[MAT_SIZE][MAT_SIZE]) {
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int main() {

	srand(time(0));
	double StartTime, EndTime;
	double StaticTime, DynamicTime, SeqTime;
	//initialize matrices
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < MAT_SIZE; j++) {
			A[i][j] = (double)rand() / RAND_MAX;
			//B[i][j] = 1.0;
			B[i][j] = (double)rand() / RAND_MAX;
			C[i][j] = 0.0;
			D[i][j] = 0.0;
		}
	}
	//printf("Matrix A:\n");
	//print(A);
	//printf("Matrix B:\n");
	//print(B);
	//print(C);

	omp_set_num_threads(NUM_THREADS);

	//Static Mapping
	//the rows of the matrix are assigned in round robin fashion to the different threads
	StartTime = omp_get_wtime();
	#pragma omp parallel
	{
		int i, j, k;
		int id = omp_get_thread_num();
		if(id==0){
		//	printf("#Threads: %d\n", omp_get_num_threads());
		}
		for (i = 0; i * NUM_THREADS + id < MAT_SIZE; i++) {
			for (j = 0; j < MAT_SIZE; j++) {
				for (k = 0; k < MAT_SIZE; k++) {
					C[i * NUM_THREADS + id][j] += A[i * NUM_THREADS + id][k] * B[k][j];
					//printf("On thread %d\n",omp_get_thread_num());
				}
			}
			//printf("Calculate row %d On thread %d\n", i * NUM_THREADS + id, omp_get_thread_num());
		}
	}
	EndTime = omp_get_wtime();
	//printf("Static result:\n");
	//print(C);
	StaticTime = (double)EndTime - StartTime;
	printf("Static Time: %f ms\n", StaticTime * 1000);

	// Dynamica Mapping
	StartTime = omp_get_wtime();
	int row = 0;		//the index of row to be calculated
	#pragma omp parallel
	{
		int i;
		while (row < MAT_SIZE)
		{
			//printf("Thread %d\n", omp_get_thread_num());
			#pragma omp critical
			{
				i = row++;
			}
			
			if (i >= MAT_SIZE) break;
			//printf("Calculate row %d On thread %d\n", i, omp_get_thread_num());
			
			for (int j = 0; j < MAT_SIZE; j++) {
				for (int k = 0; k < MAT_SIZE; k++) {
					D[i][j] += A[i][k] * B[k][j];
				}
			}
		}

	}
	EndTime = omp_get_wtime();
	DynamicTime = (double)EndTime - StartTime;
	//printf("Dynamic result:\n");
	//print(D);
	printf("Dynamic Time: %f ms\n", DynamicTime * 1000);

	return 0;
}
