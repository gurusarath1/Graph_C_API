#include <stdio.h>
#include <stdlib.h>

typedef char DATATYPE;

typedef enum errorCodes
{
	FAILURE,
	SUCCESS

}errorCode;

typedef enum Graph_Type
{
	DIRECTED,
	UNDIRECTED

}Graph_Type;

typedef enum YES_NO
{
	NO,
	YES
}YES_NO;

typedef struct GraphVertex GraphVertex;

typedef struct GraphEdge GraphEdge;

struct GraphEdge
{
	int ToVertex;
	double Cost;
	GraphEdge* NextEdge;
};

struct GraphVertex
{
	DATATYPE* Name;
	int VertexID;
	int NumConnections; //Number of outgoing connections
	GraphEdge* EdgeList;
};

typedef struct Graph
{
	int V,E;
	Graph_Type Type;
	GraphVertex* VertexArray;
} Graph;





errorCode createEdgeUtil(Graph* g_ptr, int startVertex, int endVertex, int cost);
errorCode CreateEdge(Graph* g_ptr, int startVertex, int endVertex, int cost);
Graph CreateGraph(DATATYPE vertexNames[], int numVertex, Graph_Type type);
void printGraph(Graph g);
int* getConnectedVertices(Graph* g_ptr, int startVertex, int* NumberOfConnectedVerticesReturn);
YES_NO isVertex(Graph*g , int vertex);
YES_NO isConnected(Graph* g, int startVertex, int endVertex);
errorCode DeleteEdge(Graph* g_ptr, int startVertex, int endVertex);
errorCode deleteVertex(Graph* g_ptr, int Vertex);


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

Graph CreateGraph(DATATYPE vertexNames[], int numVertex, Graph_Type type)
{

	Graph g;
	GraphVertex* v_ary = (GraphVertex*)malloc(sizeof(GraphVertex)*numVertex);


	for(int i=0; i<numVertex; i++)
	{
		v_ary[i].Name = &vertexNames[i];
		v_ary[i].VertexID = i;
		v_ary[i].EdgeList = NULL;
		v_ary[i].NumConnections = 0;
	}

	g.V = numVertex;
	g.E = 0;
	g.Type = type;
	g.VertexArray = v_ary;

	return g;
}


errorCode createEdgeUtil(Graph* g_ptr, int startVertex, int endVertex, int cost)
{

	GraphEdge** edge = &(g_ptr->VertexArray[startVertex].EdgeList);

	GraphEdge** prevEdge = edge;

	if(*edge != NULL)
	{
		while(*edge != NULL)
		{
			prevEdge = edge;
			edge = &((*edge)->NextEdge);
		}

	} else {

		(*prevEdge) = (GraphEdge*) malloc(sizeof(GraphEdge));
		(*prevEdge)->NextEdge = NULL;
		(*prevEdge)->ToVertex = endVertex;
		(*prevEdge)->Cost = cost;

		g_ptr->E += 1;
		g_ptr->VertexArray[startVertex].NumConnections += 1;

		return SUCCESS;
	}

	(*prevEdge)->NextEdge = (GraphEdge*) malloc(sizeof(GraphEdge));
	(*prevEdge)->NextEdge->NextEdge = NULL;
	(*prevEdge)->NextEdge->ToVertex = endVertex;
	(*prevEdge)->NextEdge->Cost = cost;


	g_ptr->E += 1;
	g_ptr->VertexArray[startVertex].NumConnections += 1;
	return SUCCESS;
}

errorCode CreateEdge(Graph* g_ptr, int startVertex, int endVertex, int cost)
{

	if(isConnected(g_ptr, startVertex, endVertex))
	{
		printf("\nConnection Already exist!\nNo new connection created.");
		return SUCCESS;
	}

	createEdgeUtil(g_ptr, startVertex, endVertex, cost);

	if(g_ptr->Type == UNDIRECTED)
		createEdgeUtil(g_ptr, endVertex, startVertex, cost);

	return SUCCESS;
}

void printGraph(Graph g)
{

	GraphVertex* vtxAry = g.VertexArray;
	GraphEdge* edge;

	printf("\n===================================\n");
	printf("Graph:   V = %d     E = %d", g.V, g.E);
	printf("\n===================================\n");

	for(int i=0; i<g.V; i++)
	{
		printf("\n%d (%c - %d): ", vtxAry[i].VertexID, *(vtxAry[i].Name), vtxAry[i].NumConnections);

		edge = g.VertexArray[i].EdgeList;

		while(edge != NULL)
		{
			printf("%d, ", edge->ToVertex);
			edge = edge->NextEdge;
		}

	}

	printf("\n");
}

int* getConnectedVertices(Graph* g_ptr, int startVertex, int* NumberOfConnectedVerticesReturn)
{
	GraphVertex v = (g_ptr->VertexArray)[startVertex];
	GraphEdge* edge;
	edge = v.EdgeList;

	*NumberOfConnectedVerticesReturn = v.NumConnections;

	int* a = (int*)malloc(sizeof(int) * v.NumConnections);
	int i = 0;
	while(edge != NULL)
	{
		a[i++] = edge->ToVertex;
		edge = edge->NextEdge;
	}

	return a;
}

YES_NO isVertex(Graph*g , int vertex)
{

	if(vertex < 0 || vertex >= g->V)
	{
		return NO;
	}

	return YES;
}

YES_NO isConnected(Graph* g_ptr, int startVertex, int endVertex)
{

	if(!(isVertex(g_ptr, startVertex) && isVertex(g_ptr, endVertex)))
	{
		printf("\nVertex not found in graph");
		return NO; //Vertex not found
	}

	GraphVertex v = (g_ptr->VertexArray)[startVertex];
	GraphEdge* edge;
	edge = v.EdgeList;

	while(edge != NULL)
	{
		if(edge->ToVertex == endVertex)
		{
			return YES;
		}
		edge = edge->NextEdge;
	}

	return NO;
}

errorCode DeleteEdge(Graph* g_ptr, int startVertex, int endVertex)
{

	if(!isConnected(g_ptr, startVertex, endVertex))
	{
		printf("\nConnection does not exist !\nNo connection deleted");
		return SUCCESS;
	}

	GraphEdge** edge = &( (g_ptr->VertexArray)[startVertex].EdgeList );
	GraphEdge** prevEdge = edge;
	GraphEdge** nextEdge = &((*edge)->NextEdge);

	while(*edge != NULL)
	{
		prevEdge = edge;
		nextEdge = &((*edge)->NextEdge);

		if((*edge)->ToVertex == endVertex)
		{
			free(*edge);
			*prevEdge = *nextEdge;
			break;
		}

		edge = &((*edge)->NextEdge);
	}

	g_ptr->E -= 1;
	(g_ptr->VertexArray)[startVertex].NumConnections -= 1;
	return SUCCESS;
}

errorCode deleteVertex(Graph* g_ptr, int Vertex)
{




}
