#include <stdio.h>
#include <stdlib.h>
#include"GraphStructure.h"

//Cba  with tree queries

void fillAncestorsDFS(int start, int prev, int n, int ancestors[n][N]){
    Node* next = graph->adjLists[start].head;
    while (next != NULL){
        if (next->vertex == prev){
            next = next->next;
            continue;
        }
        ancestors[next->vertex][1] = start;
        fillAncestorsDFS(next->vertex,start,n,ancestors);
        next = next->next;
    }
}

void fillAncestors(int n, int ancestors[n][N]){
    for (int i=0;i<n;++i){
        for (int j=0;j<N;++j){
            ancestors[i][j]=-1;
        }
    }
    fillAncestorsDFS(0,-1,n,ancestors);

    for (int i=2;i<N;i*=2){
        for (int j=0;j<n;++j){
            if (ancestors[j][i/2] == -1) ancestors[j][i] = -1;
            else ancestors[j][i] = ancestors[ancestors[j][i/2]][i/2];
        }
    }

}

int findAncestor(int n, int ancestors[n][N],int node, int k){
    int result = node;
    for (int i=0;i<32;++i){
        if (1<<i & k) result = ancestors[node][1<<i];
    }
    printf("%dth ancestor of %d is %d.\n",k,node,result);
    return result;
}

int buildTraversalArray(int start, int prev, int* index, int* nodes, int* subtrees, int* valuesOrig, int* values){
    Node* next = graph->adjLists[start].head;
    int subTreeSize = 1;
    nodes[*index] = start;
    values[(*index)++] = valuesOrig[start];
    while (next != NULL){
        if (next->vertex == prev){
            next = next->next;
            continue;
        }
        subTreeSize += buildTraversalArray(next->vertex,start,index,nodes,subtrees,valuesOrig, values);
        next = next->next;
    }

    for (int i=0;i<graph->numVertices;++i){
        if (nodes[i] == start) {
            subtrees[i] = subTreeSize;
            break;
        }
    }
    return subTreeSize;
}

void lowestCommonAncestor(int aOrig, int bOrig, int n, int ancestors[n][N]){
    int a = aOrig, b = bOrig;
    if (a==0 ||b == 0){
        printf("Lowest common ancestor is the root.");
        return;
    }
    int distA = 1, distB = 1;
    int nextA = ancestors[a][1], nextB = ancestors[b][1];
    while (nextA != 0 || nextB != 0) {
        if (nextA != 0){
            distA++;
            nextA = ancestors[nextA][1];
        } if (nextB != 0){
            distB++;
            nextB = ancestors[nextB][1];
        }
    }
    if (distB>distA) b = findAncestor(n,ancestors,b,distB-distA);
    else if (distA < distB) a = findAncestor(n, ancestors, a, distB-distA);
    while (a != b){
        a = ancestors[a][1];
        b = ancestors[b][1];
    }
    printf("Lowest common ancestor of %d and %d is %d",aOrig,bOrig,a);
}

int main(){
    graph = createGraph(9);
    addEdge(graph,0,1,1);
    addEdge(graph,0,2,1);
    addEdge(graph,0,3,1);
    addEdge(graph,0,4,1);
    addEdge(graph,1,5,1);
    addEdge(graph,3,6,1);
    addEdge(graph,3,7,1);
    addEdge(graph,3,8,1);
    int ancestors[graph->numVertices][N];
    fillAncestors(graph->numVertices,ancestors);
    lowestCommonAncestor(5,7,graph->numVertices,ancestors);
    return 0;





















}