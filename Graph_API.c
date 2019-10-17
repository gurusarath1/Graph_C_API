#include <stdio.h>

typedef int DATA_TYPE;

typedef enum Graph_Type
{
    DIRECTED,
    UNDIRECTED

}Graph_Type;

typedef struct GraphVertex GraphVertex;
struct GraphVertex
{
    DATA_TYPE name;
    GraphVertex* AdjNode;

};

typedef struct Graph
{
    int V,E;
    Graph_Type type;
    GraphVertex* VertexArray;

} Graph;

int main()
{
    DATA_TYPE x[6] = {4,5,6,7,8,9,0};
    Graph* Gptr;
    createGraph(&Gptr, x, 6);

    printAllVerticesInGraph(Gptr);

    return 0;
}

int createGraph(Graph** G, DATA_TYPE VertexList[], int numVertex, Graph_Type type_in)
{
    *G = (Graph*)malloc(sizeof(Graph));
    GraphVertex* VertexAryX = (GraphVertex*)malloc(sizeof(GraphVertex) * numVertex);
    (*G)->V = numVertex;
    (*G)->type = type_in;

    for(int i=0; i<numVertex; i++)
    {
        VertexAryX[i].name = VertexList[i];
    }

    (*G)->VertexArray = VertexAryX;
}

int printAllVerticesInGraph(Graph* G_ptr)
{

    for(int i=0; i<G_ptr->V; i++)
    {
        printf("Vertex %d:  %d\n",i+1,G_ptr->VertexArray[i].name);
    }
    return 0;

}

int addEdgeToGraph(Graph* G, DATA_TYPE from_Vertex, DATA_TYPE to_Vertex)
{



}
