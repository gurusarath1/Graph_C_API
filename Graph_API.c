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

typedef struct GraphVertex GraphVertex;

typedef struct GraphEdge GraphEdge;

struct GraphEdge
{
	int ToVertex;
	double cost;
	GraphEdge* NextEdge;
};

struct GraphVertex
{
	DATATYPE* name;
	int vertexID;
	GraphEdge* EdgeList;
};

typedef struct Graph
{
	int V,E;
	Graph_Type type;
	GraphVertex* VertexArray;
} Graph;





errorCode CreateEdge(Graph* g_ptr, int startVertex, int endVertex, int cost);
Graph CreateGraph(DATATYPE vertexNames[], int numVertex, Graph_Type type);
void printGraph(Graph g);





int main()
{
	DATATYPE x[] = {'A','B','C','D','E','F','G'};
	int size = sizeof(x)/sizeof(DATATYPE);

	Graph g = CreateGraph(x, size, UNDIRECTED);
	CreateEdge(&g, 0, 2, 1);
	CreateEdge(&g, 1, 4, 1);
	CreateEdge(&g, 0, 5, 1);

	printGraph(g);

	return 0;
}

Graph CreateGraph(DATATYPE vertexNames[], int numVertex, Graph_Type type)
{

	Graph g;
	GraphVertex* v_ary = (GraphVertex*)malloc(sizeof(GraphVertex)*numVertex);


	for(int i=0; i<numVertex; i++)
	{
		v_ary[i].name = &vertexNames[i];
		v_ary[i].vertexID = i;
		v_ary[i].EdgeList = NULL;
	}

	g.V = numVertex;
	g.E = 0;
	g.type = type;
	g.VertexArray = v_ary;

	return g;
}


errorCode CreateEdge(Graph* g_ptr, int startVertex, int endVertex, int cost)
{

	GraphEdge* edge = g_ptr->VertexArray[startVertex].EdgeList;

	GraphEdge* prevEdge = edge;

	if(edge != NULL)
	{
		printf("\nNULL");
		while(edge != NULL)
		{
			prevEdge = edge;
			edge = edge->NextEdge;
		}

	} else {

		printf("\nElse");


		prevEdge = (GraphEdge*) malloc(sizeof(GraphEdge));
		prevEdge->NextEdge = NULL;
		prevEdge->ToVertex = endVertex;
		prevEdge->cost = cost;

		g_ptr->E += 1;

		return SUCCESS;
	}

	prevEdge->NextEdge = (GraphEdge*) malloc(sizeof(GraphEdge));
	prevEdge->NextEdge->NextEdge = NULL;
	prevEdge->NextEdge->ToVertex = endVertex;
	prevEdge->NextEdge->cost = cost;

	g_ptr->E += 1;
	return SUCCESS;
}

void printGraph(Graph g)
{

	GraphVertex* vtxAry = g.VertexArray;
	GraphEdge* edge;


	for(int i=0; i<g.V; i++)
	{
		printf("\n%d : ", vtxAry[i].vertexID);

		edge = g.VertexArray[i].EdgeList;

		while(edge != NULL)
		{
			printf("%d, ", edge->ToVertex);
			edge = edge->NextEdge;
		}

	}

	printf("\n");

}
