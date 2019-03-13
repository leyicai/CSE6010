/*
 * main.c
 *
 *  Created on: 2018Äê8ÔÂ31ÈÕ
 *      Author: CAI
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"Functions.h"

int main(){
	int n1=2;
	int n2=3;
	int n3=5;

	double** matA;
	double** matB;
	double** matC;

	//Initialize rand() seed.
	srand((unsigned)time(0));

	//Initialize matrix A
	matA=malloc_matrix(n1,n2);
	fill_matrix(n1,n2,matA);
	printf("Matrix A:\n");
	print_matrix(n1,n2,matA);

	//Initialize matrix B
	matB=malloc_matrix(n2,n3);
	fill_matrix(n2,n3,matB);
	printf("Matrix B:\n");
	print_matrix(n2,n3,matB);

	//Initialize matrix C
	matC=malloc_matrix(n1,n3);

	//matrix C=matrix A multiplies matrix B
	matrix_multiply(n1, n2, n3, matA, matB, matC);

	//Print matrix C
	printf("A multiplies B equals:\n");
	print_matrix(n1,n3,matC);

	//free all the address
	free_matrix(n1,n2,matA);
	free_matrix(n2,n3,matB);
	free_matrix(n1,n3,matC);

	return 0;
}
