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
