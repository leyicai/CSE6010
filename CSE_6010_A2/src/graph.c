/*
 * graph.c
 *
 *  Created on: Sep 14, 2018
 *      Author: Leyi Cai
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int Grid_Generate(int K, int P, int** grid) {

	int i, j, color = 0;

	for (i = 0; i < K; i ++ ) {
		for (j = 0; j < K; j ++) {
			if ( rand() % 1000 < P )	//probability of colored cell is P/1000
				grid[j][i] = color ++;		//use increasing numbers to represent colored cells
			else grid[j][i] = K * K;	//use K*K to represent the uncolored nodes
		}
	}

	return color;	//return the number of colored cells
}

void Convert_Graph(int** grid, int K, vertex** graph) {

	for (int j = 0; j < K; j ++) {
		for (int i = 0; i < K; i ++) {
			int num = 0;
			if (grid[i][j] != K * K) {
				//create the first node of a linked list
				num = grid[i][j];
				vertex* v = (vertex*) malloc (sizeof(vertex));
				if (v == NULL) {
					printf("Allocation Error!\n");
					return;
				}
				v -> index = num;
				v -> firstedge = NULL;

				//left neighbor
				if ( j - 1 >= 0 && grid[i][j - 1] != K * K) {
					Add_Edge(v, grid[i][j - 1]);
				}
				//up neighbor
				if ( i - 1 >= 0 && grid[i - 1][j] != K * K) {
					Add_Edge(v, grid[i - 1][j]);
				}
				//down neighbor
				if ( i + 1 < K && grid[i + 1][j] != K * K) {
					Add_Edge(v, grid[i + 1][j]);
				}
				//right neighbor
				if ( j + 1 < K && grid[i][j + 1] != K * K) {
					Add_Edge(v, grid[i][j + 1]);
				}

				//add the linked list into graph
				graph[num] = v;

			}
		}
	}
}

void Add_Edge(vertex* v, int ind) {
	edge* p;

	//create node e
	edge* e = (edge*) malloc (sizeof(edge));
	if (e == NULL) {
		printf("Allocation Error!\n");
		return;
	}
	e -> index = ind;
	e -> next = NULL;

	//if node e will be the first node after vertex v
	if (v -> firstedge == NULL) {
		v -> firstedge = e;
	}

	else {
		p = v -> firstedge;

		//find the right place to put node e
		while (p -> next) {
			p = p -> next;
		}

		//put node into the linked list
		p -> next = e;
	}
}

int Write_File(char* str, vertex** graph, int ver_num) {

	FILE *fp;
	fp = fopen(str, "w");
	if (fp == NULL) {
		printf("Open Error!\n");
		return 0;
	}

	fprintf(fp, "%d\n", ver_num);	//first line of output: number of vertices
	for (int i = 0; i < ver_num; i++) {
		//first node of every adjacent list
		fprintf(fp, "%d ", graph[i] -> index);
		edge* temp = graph[i] -> firstedge;
		while (temp) {
			//rest nodes of the adjacent list
			fprintf(fp, "%d ", temp -> index);
			temp = temp -> next;
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	return 1;
}

int DFS(vertex** graph, vertex* u, cmp* p, int* visit) {

	int ind;
	ind = u -> index;
	p -> size ++;
	visit[ind] = 1;		//set node u as visited

	//if vertex u has no adjacent node
	if (u -> firstedge == NULL) {
		return 0;
	}

	//else, consider all adjacent vertices of u
	edge* v = u -> firstedge;
	while (v) {
		//if v is not visited, DFS all its adjacent node
		if (visit[v -> index] == 0) {
			vertex* v_ver = graph[v -> index];
			DFS(graph, v_ver, p, visit);
		}
		v = v -> next;
	}
	return 0;
}

int Out_File(char* str, cmp* head, int ver_num) {

	cmp* ptr = head -> next;	//the first components node
	FILE* ofp = fopen(str, "w");
	if (ofp == NULL) {
		printf("File Open Failure!\n");
		return 0;
	}
	int largest = 0;	//size of largest component
	int count = 0;		//number of components

	//go through the linked list of components
	while (ptr) {
		count ++;
		if (ptr -> size > largest) {
			largest = ptr -> size;
		}
		ptr = ptr -> next;
	}
	fprintf(ofp, "%d\n", count);
	fprintf(ofp, "%f\n", (float)ver_num / count);	//average size of components
	fprintf(ofp, "%d\n", largest);

	//get the histogram of distribution
	ptr = head -> next;
	histogram(ofp, ptr, largest);

	fclose(ofp);
	return 1;

}
void histogram(FILE* ofp, cmp* ptr, int largest) {

	//dist is an array to store the distribution of component sizes
	int* dist = (int*) malloc (largest * sizeof(int));
	if (dist == NULL) {
		printf("Allocation Error!\n");
		return;
	}
	for (int i = 0; i < largest; i++) {
		dist[i] = 0;
	}

	//go through the linked list of components
	while (ptr) {
		dist[ptr -> size - 1] += 1;
		ptr = ptr -> next;
	}

	for (int i = 0; i < largest; i++) {
		fprintf(ofp, "%d  %d\n", i + 1, dist[i]);
	}
	free(dist);
}
