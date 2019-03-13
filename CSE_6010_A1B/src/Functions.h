/*
 * Functions.h
 *
 *  Created on: 2018Äê8ÔÂ31ÈÕ
 *      Author: CAI
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

double **malloc_matrix(int n1, int n2);
void free_matrix (int n1, int n2, double **a);
void fill_matrix(int n1, int n2, double **a);
void print_matrix(int n1, int n2, double **a);
int matrix_multiply(int n1, int n2, int n3,double **a, double **b, double **c);

#endif /* FUNCTIONS_H_ */
