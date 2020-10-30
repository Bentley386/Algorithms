#pragma once
#include <stdlib.h>
#include <stdio.h>

#define INF 1000000001
#define N 100

int min(int,int);
int max(int,int);

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

Graph* graph; //global object graph that we use for testing
int Edges[N][3];
int eIndex;
int visited[N]; //List of visited nodes, used for dfs. Can only be used once.

Node* createNode(int);
Graph* createGraph(int);
void addEdge(Graph*,int,int,int);
void addDirectedEdge(Graph*,int,int,int);
void printGraph(Graph*);