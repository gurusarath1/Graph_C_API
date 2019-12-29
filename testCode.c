#include "Graph_API.h"
#include <stdio.h>

int main()
{
	DATATYPE x[] = {'A','B','C','D','E'};
	int size = sizeof(x)/sizeof(DATATYPE);

	Graph g = CreateGraph(x, size, DIRECTED);
	CreateEdge(&g, 0, 2, 1);
	CreateEdge(&g, 1, 2, 1);
	CreateEdge(&g, 3, 1, 1);
	CreateEdge(&g, 4, 3, 1);
	CreateEdge(&g, 0, 4, 1);
	CreateEdge(&g, 0, 3, 1);
	CreateEdge(&g, 1, 3, 1);
	CreateEdge(&g, 4, 2, 1);

	CreateEdge(&g, 1, 2, 1);
	CreateEdge(&g, 4, 2, 2);

	printGraph(g);

	int n = 0;
	int *a = getConnectedVertices(&g, 4, &n);

	printf("\nNumber of connections to vertex 4 = %d\n", n);
	for(int i=0; i<n; i++)
	{
		printf("%d  ", a[i]);
	}

	printf("\n");

	DeleteEdge(&g, 0, 2);
	DeleteEdge(&g, 4, 3);
	DeleteEdge(&g, 3, 1);

	printGraph(g);

	return 0;
}
