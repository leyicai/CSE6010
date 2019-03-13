/*
 * Function.c
 *
 *  Created on: Sep 9, 2018
 *      Author: leyic
 */

#include <stdio.h>
#include <stdlib.h>
#include "Function.h"


//Create a new priority queue and return a pointer to it.
PrioQ* PQ_create(){

	PrioQ* PQ;
	PQ = (PrioQ *) malloc (sizeof (PrioQ));
	if (PQ == NULL)		//If malloc fails.
	{
		printf("Error!\n");
		return NULL;
	}

	//Create the head node of priority queue
	PQ -> Key = -1023;
	PQ -> Data = NULL;
	PQ -> next = NULL;

	return PQ;
}

//Insert the item pointed to by data into the priority queue PQ. The priority of this data item is key.
int PQ_insert(PrioQ* PQ, double key, void *data){

	if(PQ == NULL){
		printf("Priority queue is not created.\n");
	}

	PrioQ *pre;		//To store the pointer of the item before the new one.
	pre = PQ;
	PrioQ *new;		//Pointer of the new item.

	//Create the new item.
	new = (PrioQ *) malloc (sizeof (PrioQ));
	if (new == NULL)		//if malloc fails
	{
		printf("error!\n");
		return 0;
	}
	new -> Key = key;
	new -> Data = data;
	new -> next = NULL;

	while( (pre -> next) != NULL){
		while(key > (pre -> next -> Key)){
			pre = pre -> next;
			if( (pre -> next) == NULL){
				break;
			}
		}break;
	}

	new -> next = pre -> next;
	pre -> next = new;

	return 1;

}


//Remove the data item from the priority queue PQ with the smallest key (priority).
void *PQ_delete(PrioQ *PQ, double *key){

	if(PQ == NULL){
		printf("Priority queue is not created.\n");
	}

	void* del_data;
	PrioQ* pq;

	if (PQ -> next == NULL)		//The priority queue is empty
		return NULL;

	pq = PQ -> next;		//pq is the pointer of the first item.
	del_data = pq -> Data;
	*key = pq -> Key;

	//Update the head node
	PQ -> next = pq -> next;

	free(pq);

	return del_data;
}

//Returns the number of items currently residing in the priority queue.
unsigned int PQ_count(PrioQ *PQ){

	if(PQ == NULL){
		printf("Priority queue is not created.\n");
	}
	unsigned int count = 0;
	while(PQ -> next != NULL){
		count ++;
		PQ = PQ -> next;
	}
	return count;

}

//Delete the priority queue PQ by releasing all memory used by the contents of the data structure.
void *PQ_free(struct PrioQ *PQ){

	PrioQ* pq;
	if(PQ == NULL){
		printf("Priority queue is not created.\n");
	}

	while(PQ != NULL){
		pq = PQ;
		PQ = PQ -> next;
		free(pq);
	}
	free(pq);

	return NULL;

}
