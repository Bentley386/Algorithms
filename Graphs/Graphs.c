#include <stdio.h>
#include <stdlib.h>
#include"GraphStructure.h"

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
    //Perform a bfs starting from start, printing the path as you search.

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
    //Find and print all the connected component of the graph.

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
    //Check if connected component containing node "node" has a cycle.

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
    //Check if connected component that contains node "node" is bipartite.

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
    //Print shortest path from start to all other nodes in O(nm)

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
    //Use bellmanford to find if negative cycle exists.

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

int DjikstraHelper(int* processed, int* distances){
    int minValue=INF; int minIndex=INF;
    for (int i=0;i<graph->numVertices;++i){
        if (processed[i]) continue;
        if (distances[i] < minValue){
            minValue = distances[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void Djikstra(int start){
    //Find shortest path from start to all other nodes in o(m+n logn)

    int distance[N];
    for (int i=0;i<N;++i) distance[i] = INF;
    distance[start] = 0;

    int processed[N]; for(int i=0;i<N;++i) processed[i]=0;

    int numprocessed=0, currentNode;
    while (numprocessed<graph->numVertices){
        numprocessed++;
        currentNode = DjikstraHelper(processed,distance);
        processed[currentNode]=1;
        Node* n = graph->adjLists[currentNode].head;
        while (n!=NULL){
            distance[n->vertex] = min(distance[n->vertex],distance[currentNode]+n->weight);
            n = n->next;
        }
    }

    for (int i=0;i<graph->numVertices;++i){
        printf("Distance to %d: %d\n",i,distance[i]);
    }
}

void FloydWarshall(){
    //Find shortest path between all nodes in O(n^3)

    int distances[N][N];
    for (int i=0;i<graph->numVertices;++i){
        for (int j=0;j<graph->numVertices;++j){
            if (i==j) distances[i][j]=0;
            else distances[i][j] = INF;
        }
    }
    for (int i=0;i<eIndex;++i){
        distances[Edges[i][0]][Edges[i][1]] = Edges[i][2];
    }

    for (int i=0;i<graph->numVertices;++i){
        for (int j=0;j<graph->numVertices;++j){
            for (int k=0;k<graph->numVertices;++k){
                distances[i][j] = min(distances[i][j],distances[i][k]+distances[k][j]);
            }
        }
    }

    for (int i=0;i<graph->numVertices;++i){
        printf("Distance from vertex %d to:\n",i);
        for (int j=0;j<graph->numVertices;++j){
            printf("%d: %d\n",j,distances[i][j]);
        }
        printf("\n");
    }
}

void hierholzer(){
    //Find the euler walk assuming it exists.

    int* visitedEdges = malloc(sizeof(int)*eIndex); for (int i=0;i<eIndex;++i) visitedEdges[i]=0;
    int* visitedNodes = malloc(sizeof(int)*graph->numVertices); for (int i=0;i<graph->numVertices;++i) visitedNodes[i]=0;

    int* circuit = malloc(sizeof(int)*N);
    int* tempcircuit = malloc(sizeof(int)*N); 
    for (int i=0;i<N;++i) {circuit[i]=-1;tempcircuit[i]=-1;}
    int tempcircuitIndex=0;

    int processedEdges = 0;
    int currNode=6;
    visitedNodes[6] = 1;
    printf("Order of edges in the Euler walk:\n");
    while (processedEdges < eIndex){
        for (int i=0;i<graph->numVertices;++i){
            if (!visitedNodes[i]) continue;
            tempcircuitIndex=0;
            tempcircuit[tempcircuitIndex++] = i;

            for (int j=0;j<eIndex;++j){
                if (visitedEdges[j]) continue;

                if (Edges[j][0] == currNode){
                    visitedNodes[Edges[j][1]] = 1;
                    visitedEdges[j]=1; processedEdges++;
                    for (int k=0;k<eIndex;++k){
                        if (Edges[k][0] == Edges[j][1] && Edges[k][1] == Edges[j][0]){
                            visitedEdges[k]=1; processedEdges++;
                            break;
                        }
                    }
                    tempcircuit[tempcircuitIndex++] = Edges[j][1];
                    printf("%d -> %d\n",Edges[j][0],Edges[j][1]);
                    currNode = Edges[j][1];
                }
            }
            //cba with this in C. no backtracking.
            //if(circuit[0] == -1){
            //    for (int i=0;i<tempcircuitIndex;++i) circuit[i]=tempcircuit[i];
            //}
            //else {
            //    for (int i=0;i<N;++i){
            //        if (tempcircuit[0] == circuit[i]){
            //            for (int j=1;j<tempcircuitIndex;++j){
            //                circuit[i+j+tempcircuitIndex-1] = circuit[i+j];
            //                circuit[i+j]=tempcircuit[j];
            //            }
            //        }
            //    }
            //}
        }
    }
    //printf("The euler circuit goes through these nodes:\n");
    //for (int i=0;circuit[i]!=-1;++i) printf("%d ",circuit[i]);
}

int main(){
    graph = createGraph(7);
    addEdge(graph,0,1,1);
    addEdge(graph,0,2,1);
    addEdge(graph,1,2,1);
    addEdge(graph,1,5,1);
    addEdge(graph,2,5,1);
    addEdge(graph,1,4,1);
    addEdge(graph,4,5,1);
    addEdge(graph,2,3,1);
    addEdge(graph,3,6,1);
    addEdge(graph,5,6,1);
    hierholzer();
    return 0;
}

