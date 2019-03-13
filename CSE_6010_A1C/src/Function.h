/*
 * Function.h
 *
 *  Created on: Sep 9, 2018
 *      Author: leyic
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

typedef struct PrioQ{
	double Key;
	void *Data;
	struct PrioQ *next;
}PrioQ;

//Create a new priority queue and return a pointer to it.
PrioQ *PQ_create();

//Insert the item pointed to by data into the priority queue PQ. The priority of this data item is key.
int PQ_insert(PrioQ *PQ, double key, void *data);

//Remove the data item from the priority queue PQ with the smallest key (priority).
void *PQ_delete(PrioQ *PQ, double *key);

//Returns the number of items currently residing in the priority queue.
unsigned int PQ_count(PrioQ *PQ);

//Delete the priority queue PQ by releasing all memory used by the contents of the data structure.
void *PQ_free(struct PrioQ *PQ);


#endif /* FUNCTION_H_ */
