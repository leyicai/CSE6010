/*
 * 1A.c
 *
 *  Created on: 2018.8.23
 *      Author: CAI
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>		//use current time as seed for srand()

#define n 10		//define column
#define m 20		//define row
#define p 0.01		//define probability

void CreateMatrix(int *);		//Create original matrix
void ChangeMatrix(int *, int *);		//Transform original matrix
void Output(int *);

int main()
{
	int OriMat[m][n]={0};		//Original Matrix
	int OutMat[m][n]={0};		//Output Matrix
	int *p_Ori=(int *)malloc(n*m*sizeof(int));
	int *p_Out=(int *)malloc(n*m*sizeof(int));
	p_Ori=OriMat;
	p_Out=OutMat;

	CreateMatrix(p_Ori);
	Output(p_Ori);
	printf("\n");

	//Transform the matrix
	ChangeMatrix(p_Ori,p_Out);
	Output(p_Out);
	printf("\n");

	return 0;
}

void CreateMatrix(int *pa)
{
	int i,j;
	int *ptemp;		//save the address of original matrix
	ptemp=pa;
	srand((unsigned)time(0));		//initialize rand()

	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(rand()%100<(p*100)){		//the probability of "1" is p.
				*pa=1;
			}
			pa++;
		}
	}
	pa=ptemp;
}

void ChangeMatrix(int *pa,int *pb)
{
	int i,j,x,y;

	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			if(pa[i*n+j]==1)
			{
				for(x=0;x<m;x++){
					pb[x*n+j]=1;
				}
				for(y=0;y<n;y++){
					pb[i*n+y]=1;
				}
			}
		}
	}
}

void Output(int* pa){
	int i,j;
	for(i=0;i<m;i++){
		for(j=0;j<n;j++){
			printf("%2d", *pa);
			pa++;
		}
		printf("\n");
	}
}
