#include <stdio.h>
#include "Graph_API.h"
#include "./stackAPI/Stack_C_API.h"

int *closed, c_index = 0;
int *cameFrom;
Stack openList;

int DepthFirstSearch(Graph g,int start ,int goal, int firstCallFlag);
int isInList(int vertex, int* list, int size);

int main()
{

	DATATYPE x[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O'};
	int size = sizeof(x)/sizeof(DATATYPE);

	Graph g = CreateGraph(x, size, UNDIRECTED);

	CreateEdge(&g, 0, 1, 1);
	CreateEdge(&g, 0, 2, 1);
	CreateEdge(&g, 1, 3, 1);
	CreateEdge(&g, 1, 4, 1);
	CreateEdge(&g, 1, 5, 1);
	CreateEdge(&g, 3, 7, 1);
	CreateEdge(&g, 4, 6, 1);
	CreateEdge(&g, 5, 6, 1);
	CreateEdge(&g, 6, 14, 1);
	CreateEdge(&g, 7, 8, 1);
	CreateEdge(&g, 8, 9, 1);
	CreateEdge(&g, 8, 10, 1);
	CreateEdge(&g, 9, 11, 1);
	CreateEdge(&g, 10, 13, 1);
	CreateEdge(&g, 11, 12, 1);
	printGraph(g);

	closed = (int*)malloc(sizeof(int)*size);
	cameFrom = (int*)malloc(sizeof(int)*size);
	openList = CreateStack(20);

	DepthFirstSearch(g, 0, 12, 1);

	for(int i=0; i<c_index; i++)
	{
		printf("\n%d : %d", closed[i], cameFrom[closed[i]]);
	}

	printf("\n");

	return 0;
}

int DepthFirstSearch(Graph g,int start ,int goal, int firstCallFlag)
{
	if(firstCallFlag)
	{
		push(&openList, start);
	}

	if(start == goal)
	{
		return 1;
	}

	if(Stack_isEmpty(&openList))
	{
		return 0;
	}

	int n = 0;
	int *children = getConnectedVertices(&g, start, &n);

	int sizeOfOpen = 0;
	STACK_DATA *openList_Array = stackToArray(&openList, &sizeOfOpen);

	closed[c_index++] = start;

	for(int i=0; i<n; i++)
	{
		if(isInList(children[i], closed, c_index)  ||  isInList(children[i], openList_Array, sizeOfOpen) )
		{
			;

		} else {
			push(&openList, children[i]);
			cameFrom[children[i]] = start;
		}
	}

	pop(&openList, &start);
	DepthFirstSearch(g, start, goal, 0);

}

int isInList(int vertex, int* list, int size)
{

	for(int i=0; i<size; i++)
	{
		if(vertex == list[i])
		{
			return 1;
		}
	}

	return 0;
}


/*

OUTPUT

===================================
Graph:   V = 15     E = 30
===================================

0 (A - 2): 1, 2,
1 (B - 4): 0, 3, 4, 5,
2 (C - 1): 0,
3 (D - 2): 1, 7,
4 (E - 2): 1, 6,
5 (F - 2): 1, 6,
6 (G - 3): 4, 5, 14,
7 (H - 2): 3, 8,
8 (I - 3): 7, 9, 10,
9 (J - 2): 8, 11,
10 (K - 2): 8, 13,
11 (L - 2): 9, 12,
12 (M - 1): 11,
13 (N - 1): 10,
14 (O - 1): 6,

0 : 0
2 : 0
1 : 0
5 : 1
6 : 5
14 : 6
4 : 1
3 : 1
7 : 3
8 : 7
10 : 8
13 : 10
9 : 8
11 : 9



*/
