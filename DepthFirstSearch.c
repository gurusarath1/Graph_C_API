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

	closed[c_index++] = start;

	for(int i=0; i<n; i++)
	{
		if(isInList(children[i], closed, c_index))
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
