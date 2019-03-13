/*
 * main.c
 *
 *  Created on: Sep 9, 2018
 *      Author: leyic
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Function.h"

int print(PrioQ * PQ){
	PQ = PQ->next;
	double data;
	if (PQ == NULL){
		printf("The priority queue is empty!\n");
		return 0;
	}
	while(PQ != NULL){
		data = *(double*)(PQ -> Data);
		printf("Key: %.2f, Data: %.2f\n", PQ -> Key, data);
		PQ = PQ -> next;
	}
	printf("\n");
	return 0;

}
int main(){

	int count = 0;
	int i;
	double* data;
	double key;
	PrioQ* PQ;

	srand(time(0));

	PQ = PQ_create();

	//Insert items into priority queue
	for (i = 0; i < 20; i++){

		data = (void*) malloc (sizeof (void));
		key = rand()%1001*0.01;
		*data = rand()%1001*0.01;
		PQ_insert(PQ, key, data);

	}

	count = PQ_count(PQ);
	printf("Number of items in PQ: %d\n", count);
	print(PQ);

	//Delete items
	double del_key;

	for(i = 0; i < 20; i++){
		PQ_delete(PQ, &del_key);
		count = PQ_count(PQ);
		printf("The Key of the removed item is %.2f.\n", del_key);
		printf("Current number of items in PQ: %d\n\n", count);
	}

	//Free the priority queue
	printf("Free PQ.\n");
	PQ_free(PQ);
	count = PQ_count(PQ);
	printf("Current number of items in PQ: %d\n", count);
	print(PQ);

	return 0;
}

