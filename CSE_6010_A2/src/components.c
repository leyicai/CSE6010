/*
 * components.c
 *
 *  Created on: Sep 14, 2018
 *      Author: Leyi Cai
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"graph.h"

int main(int argc, char* argv[]) {

	int i, j;

	/*****Read Input File*****/
	FILE* ifp = fopen(argv[1], "r");
	if (ifp == NULL) {
		printf("File Open Failure!\n");
		return 0;
	}

	int buf_size = 100;
	int len;	//length of buf
	char* buf = (char*) malloc (buf_size * sizeof(char));	//buf is to store temp data reading from fgets()
	if (buf == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}

	int ver_num = 0;
	fgets(buf, sizeof(buf), ifp);	//read the first line of input
	for (i = 0; buf[i] != 10; i++) {
		ver_num = ver_num * 10 + buf[i] - '0';
	}

	vertex** graph = (vertex**) malloc (ver_num * sizeof(vertex*));
	if (graph == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}

	//read all linked lists of the graph from the input file
	int ver_ind;
	for (i = 0; i < ver_num; i++) {
		//create the first node of linked list
		vertex* v = (vertex*) malloc (sizeof(vertex));
		if (v == NULL) {
			printf("Allocation Error!\n");
			return 0;
		}
		v -> index = i;
		v -> firstedge = NULL;

		fgets(buf, sizeof(buf), ifp);

		//if current buf is not big enough to store the entire line
		while (strrchr(buf, '\n') == NULL) {
			buf_size += 10;
			buf = (char*)realloc(buf, buf_size);
			if (buf == NULL) {
				printf("Allocation Error!\n");
				return 0;
			}
			len = (int)strlen(buf);		//get the current end positon in buf
			if (fgets(buf + len, buf_size - len, ifp) == NULL)
				break;
		}

		//store the rest vertices of the linked list
		ver_ind = 0;
		for ( j = 0; buf[j] != 10; j++) {

			if (buf[j] == ' ') {	//next vertex
				if (ver_ind != i) {
					Add_Edge(v, ver_ind);
				}
				ver_ind = 0;
				continue;
			}
			ver_ind = ver_ind * 10 + buf[j] - '0';
		}

		//store the linked list in to the graph
		graph[i] = v;

	}
	fclose(ifp);


	/*****Analyze the Graph*****/

	//set an array to store visited status
	int* visit = (int*) malloc(ver_num * sizeof(int));
	if (visit == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}
	for (i = 0; i < ver_num; i++) {
		visit[i] = 0;	//set 0 as color white for DFS
	}

	//initialize a pointer to store info of components
	cmp* head = (cmp*) malloc (sizeof(cmp));
	if (head == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}
	head -> size = 0;
	head -> next = NULL;
	cmp* ptr = head;

	//DFS the whole grid
	for (i = 0; i < ver_num; i++) {
		if (visit[i] == 0) {
			cmp* component = (cmp*) malloc (sizeof(cmp));
			if (component == NULL) {
				printf("Allocation Error!\n");
				return 0;
			}
			component -> size = 0;
			component -> next = NULL;

			DFS(graph, graph[i], component, visit);

			ptr -> next = component;
			ptr = ptr -> next;

		}
	}

	/*****Output the Analysis*****/
	if (!Out_File(argv[2], head, ver_num)) {
		printf("Output Error!\n");
		return 0;
	}

	/*****Free Memory*****/
	for (int i = 0; i < ver_num; i++) {
		edge* temp = graph[i] -> firstedge;
		while (temp) {
			edge* t_free = temp;
			temp = temp -> next;
			free(t_free);
		}
		free(graph[i]);
	}
	free(graph);

	free(visit);

	ptr = head;
	while (head) {
		ptr = head;
		head = head -> next;
		free(ptr);
	}

	return 1;

}
