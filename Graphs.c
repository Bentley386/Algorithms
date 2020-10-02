#include <stdio.h>
#include <stdlib.h>

#define INF 2000000001
#define N 10000

int min(int a, int b){
    return (a<b) ? a : b;
}

int Edges[N][3];
int eIndex;

typedef struct Node {
    int vertex;
    struct Node* next;
    int weight;
} Node;

typedef struct {
    Node* head;
    int weight;
} AdjList;

typedef struct {
    int numVertices;
    AdjList* adjLists;
} Graph;


Node* createNode(int num){
    //Create node with vertex number num

    Node* node = malloc(sizeof(Node));
    node->vertex = num;
    node->next = NULL;
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

void printGraph(Graph* graph){
    //Print adj. list of graph

    for (int i=0;i<graph->numVertices;++i){
        Node* j = graph->adjLists[i].head;
        printf("Vertex %d is adj. to: ",i);
        while (j != NULL){
            printf("%d ",j->vertex);
            j = j->next;
        }
        printf("\n");
    }
}

Graph* graph; //global object graph that we use for testing
int visited[N]; //List of visited nodes, used for dfs. Can only be used once.

void dfs(int node, int printpath){
    //Preform a dfs starting from node. Print the path as you go if printpath!=0

    if(visited[node]) return;
    visited[node]=1;
    if (printpath) printf("Visiting: %d\n", node);
    Node* next = graph->adjLists[node].head;
    while (next != NULL){
        dfs(next->vertex, printpath);
        next = next->next;
    }
}

void bfs(int start){
    //Perform a bfs starting from start.

    int node;
    int queue[N], visited[N],distances[N]; 
    for(int i=0;i<N;++i) {queue[i]=0; visited[i]=0; distances[i]=0;}
    int pushindex=0, popindex=0;
    visited[start]=1;
    queue[pushindex++]=start;
    while (popindex<pushindex){
        node = queue[popindex++];
        printf("Node: %d, distance from start: %d\n",node,distances[node]);
        Node* n = graph->adjLists[node].head;
        while (n != NULL){
            if (visited[n->vertex]){
                n = n-> next;
                continue;
            }
            visited[n->vertex] = 1;
            queue[pushindex++] = n->vertex;
            distances[n->vertex] = distances[node]+1;
            n = n->next;
        }
    }
}

void connectedComponents(){
    //Find all connected component of the graph.

    int visited2[N]; for(int i=0;i<N;++i) visited2[i]=0;
    int comps = 1;
    int visitedNodes=0;
    int whereToStart=0;

    while (visitedNodes < graph->numVertices){
        printf("Component %d: ",comps++);
        dfs(whereToStart,0);
        for (int i=0;i<graph->numVertices;++i){
            if (visited[i] && !visited2[i]) {
                printf("%d ",i); 
                visitedNodes++;
                visited2[i]=1;
            }
            else whereToStart=i;
        }
        printf("\n");
    }
}

void cycleCheck(int prev, int node){
    //Check if connected component containing node node has a cycle.

    if (visited[node]) return;
    visited[node]=1;
    AdjList adj = graph->adjLists[node];
    Node* n = adj.head;
    while (n != NULL){
        if (visited[node] && visited[prev]) {
            printf("Cycle found!\n");
            return;
        }
        cycleCheck(node,n->vertex);
        n = n->next;
    }
}

int colors[N];
void bipartiteness(int node, int color){
    //Check if connected component that contains node node is bipartite.

    if (visited[node]) return;
    visited[node] = 1;
    colors[node] = color;
    AdjList adj = graph->adjLists[node];
    Node* next = adj.head;
    while (next != NULL){
        if(colors[next->vertex] == color){
            printf("Not bipartite!\n");
            return;
        }
        bipartiteness(next->vertex,-color);
        next = next->next;
    }
}

void BellmanFord(int start){
    int distance[N];
    for (int i=0;i<N;++i) distance[i] = INF;
    distance[start]=0;
    for (int i=0;i<graph->numVertices; ++i){
        for (int j=0;j<eIndex;++j){
            distance[Edges[j][1]] = min(distance[Edges[j][1]],distance[Edges[j][0]]+Edges[j][2]);
        }
    }
    for (int i=0;i<graph->numVertices;++i){
        printf("Distance to %d: %d\n",i,distance[i]);
    }
}

void CheckNegCycle(int start){
    int distance[N];
    for (int i=0;i<N;++i) distance[i] = INF;
    distance[start]=0;
    int hasNegCycle=0;
    for (int i=0;i<=graph->numVertices; ++i){
        for (int j=0;j<eIndex;++j){
            if (i==graph->numVertices){
                if (distance[Edges[j][1]] != min(distance[Edges[j][1]],distance[Edges[j][0]]+Edges[j][2])){
                    hasNegCycle=1;
                    break;
                } 
            }
            else distance[Edges[j][1]] = min(distance[Edges[j][1]],distance[Edges[j][0]]+Edges[j][2]);
        }
    }
    if (hasNegCycle) printf("Negative cycle found.");
    else printf("No negative cycles found.");
}


int main(){
    graph = createGraph(4);
    addEdge(graph,0,1,3);
    addEdge(graph,0,2,5);
    addEdge(graph,1,2,2);
    addEdge(graph,1,3,1);
    addEdge(graph,2,3,7);
    printGraph(graph);
    BellmanFord(0);
    return 0;
}

