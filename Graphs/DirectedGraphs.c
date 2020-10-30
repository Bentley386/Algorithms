#include <stdio.h>
#include <stdlib.h>
#include"GraphStructure.h"

void dfsForTopSort(int node, int* processed,int* numProcessed,int* topSort){
    if (processed[node] == 2) return;
    processed[node]=1;
    Node* next = graph->adjLists[node].head;
    while (next != NULL){
        if (processed[next->vertex] == 1){
            *numProcessed = -INF;
            return;
        }
        dfsForTopSort(next->vertex,processed,numProcessed,topSort);
        next = next->next;
    }
    processed[node]=2;
    if (*numProcessed < 0) return;
    topSort[(*numProcessed)++] = node;
}

void topologicalSort(int* topSort){
    //Finds topological sort of a directer graph and stores it in topSort.

    int* processed = malloc(sizeof(int)*graph->numVertices);
    for (int i=0;i<graph->numVertices;++i) processed[i]=0;
    int numProcessed=0;
    while (numProcessed<graph->numVertices){
        for (int i=0;i<graph->numVertices;++i){
            if (processed[i]) continue;
            dfsForTopSort(i,processed,&numProcessed,topSort);
            if (numProcessed < 0){
                printf("The graph contains a cycle and can't be topologically sorted.\n");
                return;
            }
        }
    }
    printf("Topological sort: ");
    for (int i=graph->numVertices-1;i>=0;--i) printf("%d ",topSort[i]); 

}

void countNumPaths(int start){
    //Count number of paths between any two vertices using topological sort.

    int n=graph->numVertices;
    int paths[graph->numVertices]; for(int i=0;i<n;++i) paths[i]=0;
    int* topSort = malloc(sizeof(int)*n);
    topologicalSort(topSort);
    paths[start]=1;
    int passedStart=0;
    for (int i=0;i<n;++i){
        if (!passedStart){
            if (topSort[n-i-1]==start) passedStart++;
            continue;
        }
        for (int j=0;j<eIndex;++j){
            if(Edges[j][1] == topSort[n-i-1]) paths[topSort[n-i-1]]+=paths[Edges[j][0]];
        }
    }
    printf("Total number of ways to get to certain nodes, starting from node %d:\n",start);
    for (int i=0;i<n;++i){
        printf("To node %d: %d\n",i,paths[i]);
    }
}

void populateSucc(int n,int succ[n][N]){
    //Prepare the array for successor queries.

    for (int i=0;i<n;++i){
        Node* next = graph->adjLists[i].head;
        succ[i][1] = next->vertex;
    }
    for (int i=2;i<N;i*=2){
        for (int j=0;j<n;++j){
            succ[j][i]= succ[succ[j][(int)i/2]][(int)i/2];
        }
    }
}

void useSucc(int n, int succ[n][N], int start, int steps){
    //Quickly find steps-th successor of node start.

    int result = start;
    for (int i=0;i<32;++i){
        if (1<<i & steps){
            result = succ[result][1<<i];
        }
    }
    printf("The %d-th successor of %d is %d.",steps,start,result);
}

void floyd(int n, int succ[n][N],int start){
    //Floyd's alorithm for finding a cycle.

    int a = succ[start][1];
    int b = succ[start][2];
    while(a != b){
        a = succ[a][1];
        b = succ[b][2];
    }
    a = start;
    while (a != b){
        a = succ[a][1];
        b = succ[b][1];
    }
    printf("The first node of the cycle is %d\n",a);
    b = succ[a][1];
    int length=1;
    while (a != b){
        b =  succ[b][1];
        length++;
    }
    printf("And the length of the cycle is %d",length);
}

void kosarajuDFS1(int start,int* visited,int* order,int* index){
    visited[start]=1;
    Node* next = graph->adjLists[start].head;
    while (next != NULL){
        if (!visited[next->vertex])
            kosarajuDFS1(next->vertex,visited,order, index);
        next = next->next;
    }
    order[(*index)++] = start;
}

void kosarajuDFS2(int start, int* visited){
    if (visited[start]) return;
    visited[start]=1;
    printf("%d ", start);

    for (int i=0;i<eIndex;++i){
        if (Edges[i][0] != start) continue;
        kosarajuDFS2(Edges[i][1],visited);
    }
}

void kosaraju(){
    //Find strongly connected components.

    int* order = malloc(sizeof(int)*graph->numVertices);
    for (int i=0;i<graph->numVertices;++i) order[i]=0;
    int* visited = malloc(sizeof(int)*graph->numVertices); for(int i=0;i<graph->numVertices;++i) visited[i]=0;
    int index=0;
    for (int i=0;i<graph->numVertices;++i){
        if (visited[i]) continue;
        kosarajuDFS1(i,visited,order,&index);
    }
    int temp;
    for (int i=0;i<eIndex;++i){
        temp = Edges[i][1];
        Edges[i][1] = Edges[i][0];
        Edges[i][0] = temp;
    }

    for (int i=0;i<graph->numVertices;++i) visited[i]=0;
    for (int i=graph->numVertices-1;i>=0;--i){
        if (visited[order[i]]) continue;
        printf("Strongly connected component: ");
        kosarajuDFS2(order[i],visited);
        printf("\n");
    }
}

int fordFulkersonDFS(int node, int* visited, int* visitedEdges, int* edgeIndex, int sink,int maxflow){
    visited[node]=1;

    if (node == sink) return maxflow;
    int value=INF;
    for (int i=0;i<eIndex;++i){
        if(visited[Edges[i][1]]) continue;
        if(Edges[i][0] != node) continue;
        if(Edges[i][2] <= 0) continue;

        value = fordFulkersonDFS(Edges[i][1],visited,visitedEdges,edgeIndex,sink,min(maxflow,Edges[i][2]));
        if (value != INF) {
            visitedEdges[(*edgeIndex)++] = i;
            break;
        }
    }

    return value;

}

void fordFulkerson(int source, int sink){
    //Find max flow/ min cut of a directed graph.
    for (int i=0;i<eIndex;++i){
        Edges[i+eIndex][0] = Edges[i][1];
        Edges[i+eIndex][1] = Edges[i][0];
        Edges[i+eIndex][2] = 0;
    }
    eIndex+=eIndex;
    int* visitedEdges = malloc(sizeof(int)*eIndex);
    int edgeIndex=0;
    int* visited = malloc(sizeof(int)*graph->numVertices);
    int val=0;
    int maxFlow=0;
    for (;;){
        for (int i=0;i<graph->numVertices;++i) visited[i]=0;
        for (int i=0;i<eIndex;++i) visitedEdges[i]=0; edgeIndex=0;
        val = fordFulkersonDFS(source,visited,visitedEdges,&edgeIndex,sink,INF);
        if (val == INF) break;

        for (int i=0;i<edgeIndex;++i){
            int edge = visitedEdges[i];
            if (edge < eIndex/2){
                Edges[edge][2] -= val;
                Edges[edge+eIndex/2][2] += val;
            } else {
                Edges[edge][2] -= val;
                Edges[edge-eIndex/2][2] += val;
            }
        }
        maxFlow+=val;
    }
    printf("The maximum flow is %d.",maxFlow);
}

void maximumMatchingBipartite(int *colorA, int sizeA){
    //Find max. matching of a bipartite graph with the help of min cut.
    
    int n = graph->numVertices;
    int source =n,  sink = n+1;
    for (int i=0;i<eIndex;++i) {
        Edges[i][0] = 0; Edges[i][1]=0;Edges[i][2]=0;
    }
    eIndex=0;
    for (int i=0;i<n;++i){
        int inA=0;
        for (int j=0;j<sizeA;++j){
            if (colorA[j] == i) {
                inA=1;
                break;
            }
        }
        if (inA){
            Node* n = graph->adjLists[i].head;
            while (n != NULL){
                Edges[eIndex][0] = i;
                Edges[eIndex][1] = n->vertex;
                Edges[eIndex++][2] = 1;
                n = n->next;
            }
            Edges[eIndex][0] = source;
            Edges[eIndex][1] = i;
            Edges[eIndex++][2] = 1;
        } else {
            Edges[eIndex][0] = i;
            Edges[eIndex][1] = sink;
            Edges[eIndex++][2] = 1;
        }
    }
    graph->numVertices = graph->numVertices + 2;
    printf("The number of maximum matching is equal to max flow and..\n");
    fordFulkerson(source,sink);
}

int main(){
    graph = createGraph(8);
    //printGraph(graph);
    addEdge(graph,0,4,1);
    addEdge(graph,1,6,1);
    addEdge(graph,2,4,1);
    addEdge(graph,2,5,1);
    addEdge(graph,2,7,1);
    addEdge(graph,3,6,1);
    int colorA[4] = {0,1,2,3};
    maximumMatchingBipartite(colorA,4);
    return 0;
}

