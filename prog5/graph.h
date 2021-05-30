typedef struct graphObj{int n; int** matrix;} graphObj;
typedef graphObj* graph;

graph createGraph(int num);

void destructGraph(graph g);

void addEdge(graph g, int i, int j);

void removeEdge(graph g, int i, int j);

int hasEdge(graph g, int i, int j);

void outEdges(graph g, int i, node** list);

void inEdges(graph g, int j, node** list);

void printGraph(graph g);

int getNumVer(graph g);
