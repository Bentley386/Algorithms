#include"GraphStructure.h"

int min(int a, int b){
    return (a<b) ? a : b;
}
int max(int a, int b){
    return (a<b) ? b : a;
}

Node* createNode(int num){
    //Create node with vertex number num

    Node* node = malloc(sizeof(Node));
    node->vertex = num;
    node->next = NULL;
    node->weight = 0;
    return node;
}

Graph* createGraph(int numVerts){
    //Create graph with numVerts vertices

    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = numVerts;
    graph->adjLists =  malloc(numVerts*sizeof(AdjList));
    for (int i=0;i<numVerts;++i) {
        graph->adjLists[i].head = NULL;
        graph->adjLists[i].weight = 0;
    }
    return graph;
}

void addEdge(Graph* graph, int a, int b, int w){
    //Add edge between vertices a and b in graph

    Edges[eIndex][0] = a; Edges[eIndex][1] = b; Edges[eIndex++][2] = w;

    Node* node = createNode(b);
    node->next = graph->adjLists[a].head;
    node->weight = w;
    graph->adjLists[a].head = node;
    graph->adjLists[a].weight = w;

    if(a==b) return;

    Edges[eIndex][0] = b; Edges[eIndex][1] = a; Edges[eIndex++][2] = w;

    node = createNode(a);
    node->next = graph->adjLists[b].head;
    node->weight = w;
    graph->adjLists[b].head = node;
    graph->adjLists[b].weight = w;
}

void addDirectedEdge(Graph* graph, int a, int b, int w){
    //Add edge between vertices a and b in graph

    Edges[eIndex][0] = a; Edges[eIndex][1] = b; Edges[eIndex++][2] = w;

    Node* node = createNode(b);
    if (graph->adjLists[a].head == NULL){
        graph->adjLists[a].head = node;
        graph->adjLists[a].weight = w;
    } else {
        node->next = graph->adjLists[a].head;
        node->weight = graph->adjLists[a].weight;
        graph->adjLists[a].head = node;
        graph->adjLists[a].weight = w;
    }
}

void printGraph(Graph* graph){
    //Print adj. list of graph

    for (int i=0;i<graph->numVertices;++i){
        Node* j = graph->adjLists[i].head;
        printf("Vertex %d is adj. to: ",i);
        if (j==NULL) printf("None");
        while (j != NULL){
            printf("%d ",j->vertex);
            j = j->next;
        }
        printf("\n");
    }
}

