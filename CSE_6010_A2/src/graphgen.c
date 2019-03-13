/*
 * main.c
 *
 *  Created on: Sep 14, 2018
 *      Author: Leyi Cai
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

int main(int argc, char *argv[]) {

	if (argc != 4) {
		printf("Parameters Error!\n");
		return 0;
	}
	int K = atoi(argv[1]);
	if (K > 46340) {	
	//the maximum number of int is 2^32 - 1, 
	//K*K should be no larger than it.
		printf("K is Too Large!\n");
		return 0;
	}

	int P = atof(argv[2]) * 1000;
	if (P > 1000 || P < 0) {
		printf("P is not Correct!\n");
		return 0;
	}

	/*****Create the Grid*****/
	int** grid;
	grid = (int**) malloc (K * sizeof(int*));
	if (grid == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}
	for (int i = 0; i < K; i++) {
		grid[i] = (int*) malloc (K * sizeof(int));
		if (grid[i] == NULL) {
			printf("Allocation Error!\n");
			return 0;
		}
	}
	int ver_num;	//the number of colored vertices in the generated grid
	srand(time(0));

	ver_num = Grid_Generate(K, P, grid);

	/***Print out the grid***/
	for (int i = 0; i < K; i++) {
		for (int j = 0; j < K; j++) {
			if (grid[i][j] == K * K)
				printf("__  ");
			else
				printf("%2d  ", grid[i][j]);
		}
		printf("\n");
	}
	

	/***Store the grid as adjacency lists***/
	vertex** graph = (vertex**) malloc (ver_num * sizeof(vertex*));
	if (graph == NULL) {
		printf("Allocation Error!\n");
		return 0;
	}
	Convert_Graph(grid, K, graph);

	/***Print the adjacency lists***/
	/*printf("%d\n", ver_num);
	for (int i = 0; i < ver_num; i++) {
		printf("%d ", graph[i] -> index);
		edge* temp = graph[i] -> firstedge;
		while (temp) {
			printf("%d ", temp -> index);
			temp = temp -> next;
		}
		printf("\n");
	}*/

	/*****Output Adjacency Lists into File*****/
	if(!Write_File(argv[3], graph, ver_num)){
		printf("Gen Write Error!\n");
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

	for (int i = 0; i < K; i++) {
		free(grid[i]);
	}
	free(grid);

	return 0;
}
