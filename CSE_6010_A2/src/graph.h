/*
 * graph.h
 *
 *  Created on: Sep 14, 2018
 *      Author: Leyi Cai
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <stdio.h>
#include <time.h>

/**A linked list struct to store each adjacent list**/
typedef struct edge {
	int index;
	struct edge *next; 	//next edge
} edge;

/**A struct to store the first nodes of each adjacent list**/
typedef struct vertex {
	int index;
	struct edge *firstedge;
} vertex;

/**A linked list struct to store the size of each component**/
typedef struct components {
	int size;
	struct components *next;
} cmp;

int Grid_Generate(int K, int P, int** grid);

void Convert_Graph(int** grid, int K, vertex** graph);

void Add_Edge(vertex* v, int ind);

int Write_File(char* str, vertex** graph, int ver_num);

int DFS(vertex** graph, vertex* u, cmp* p, int* visit);

int Out_File(char* str, cmp* head, int ver_num);

void histogram(FILE* ofp, cmp* ptr, int largest);

#endif /* GRAPH_H_ */
