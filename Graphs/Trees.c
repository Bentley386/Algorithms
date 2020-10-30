#include"GraphStructure.h"

int count[N];
int numInSubtree(int start, int prev){
    //Find number of nodes in each subtree.

    count[start]++;
    Node* next = graph->adjLists[start].head;
    while (next != NULL){
        if (next->vertex == prev) {
            next = next->next;
            continue;
        }
        count[start] += numInSubtree(next->vertex,start);
        next = next->next;
    }
    printf("Number of nodes in subtree of %d: %d\n",start,count[start]);
    return count[start];
}

int toLeaf[N], maxLength[N];
void treeDiameter(int start,int prev){
    //Print the tree diameter.

    Node* next = graph->adjLists[start].head;
    int numchildren=0,firstmax=0,secondmax=0;
    while (next != NULL){
        if (next->vertex == prev){
            next = next->next;
            continue;
        }
        numchildren++;
        treeDiameter(next->vertex,start);
        if (firstmax==0) firstmax = toLeaf[next->vertex];
        else {
            if (firstmax <= toLeaf[next->vertex]) {
                secondmax = firstmax;
                firstmax = toLeaf[next->vertex];
            } else secondmax = max(secondmax,toLeaf[next->vertex]);
        }
        toLeaf[start] = max(toLeaf[start],1+toLeaf[next->vertex]);
        next = next->next;
    }

    if (numchildren<2) maxLength[start]=toLeaf[start];
    else maxLength[start] = firstmax+secondmax+2;

    if (start==0){
        int diameter=0;
        for (int i=0;i<graph->numVertices;++i)
            diameter = max(diameter,maxLength[i]);
        
        printf("Diameter of the tree is %d", diameter);
    }
}

void treeDiameter2DFS(int start,int prev, int distance, int* maxDist, int* maxNode){
    Node* next = graph->adjLists[start].head;
    if (distance > *maxDist){
        *maxDist = distance;
        *maxNode = start;
    }
    while (next != NULL){
        if (next->vertex == prev){
            next = next->next;
            continue;
        }
        treeDiameter2DFS(next->vertex,start,distance+1, maxDist, maxNode);
        next = next->next;
    }

}

void treeDiameter2(){
    //Print the tree diameter.

    int maxDist=0, maxNode=0;
    treeDiameter2DFS(0,-1,0,&maxDist,&maxNode);
    treeDiameter2DFS(maxNode,-1,0,&maxDist,&maxNode);
    printf("The tree diameter is %d",maxDist);
}

int maxLengthThruChild[N], maxIndexThruChild[N], maxLengthThruParent[N];
void findMaxDistanceChild(int start, int prev){
    Node* n = graph->adjLists[start].head;
    int maxDist=0, maxChild=-1;
    while (n != NULL){
        if (n->vertex == prev){
            n = n->next;
            continue;
        }
        findMaxDistanceChild(n->vertex,start);
        if (maxDist < maxLengthThruChild[n->vertex]+1){ 
            maxDist = maxLengthThruChild[n->vertex]+1;
            maxChild = n->vertex;
        }
        n = n->next;
    }
    maxLengthThruChild[start] = maxDist;
    maxIndexThruChild[start] = maxChild;
    //TODO Check if max length goes through parent. Cba.
}

void printMaxDistances(){
    for (int i = 0;i<graph->numVertices;++i){
        int distance = max(maxLengthThruChild[i],maxLengthThruParent[i]);
        printf("Longest path starting from vertex %d: %d\n",i,distance);
        printf("MaxLthruchild: %d\n",maxLengthThruParent[i]);
    }
}

int link[N], size[N];
void initDSU(int numVertices){
    //initialize disjoint set union structure.

    for (int i=0;i<numVertices;++i) {
        link[i]=i;
        size[i]=1;
    }
}
int findRepDSU(int x){
    //find representative of the connected component node x is in.
    while (x != link[x]) x = link[x];
    return x;
}
int AreSameDSU(int a, int b){
    //Find if two nodes are in same component.
    return (findRepDSU(a) == findRepDSU(b)) ? 1 : 0;
}

void unionDSU(int a, int b){
    //Unite two components.
    a = findRepDSU(a);
    b = findRepDSU(b);
    if (size[a]<size[b]){
        size[b]+=size[a];
        link[a] = b;
    } else {
        size[a]+=size[b];
        link[b] = a;
    }
}

int cmpfunc(const void* a, const void* b){
    return -(((int*)a)[2] - ((int*)b)[2]);
}

void kruskal(){
    //Find the minimum spanning tree in O(m logm).

    initDSU(graph->numVertices);
    qsort(Edges,eIndex,3*sizeof(int),cmpfunc);
    printf("The minimum spanning tree containts the following edges:\n");
    int weight=0;
    for (int i=eIndex-1;i>=0;--i){
        if (!AreSameDSU(Edges[i][0],Edges[i][1])) {
            unionDSU(Edges[i][0],Edges[i][1]);
            printf("%d - %d\n",Edges[i][0],Edges[i][1]);
            weight+=Edges[i][2];
        }
    }
    printf("The total weight is %d.",weight);
}

int used[N];
int* primHelper(){
    static int result[3];
    int minim=INF,minimNode1=-1, minimNode2=-1;
    for (int i=0;i<graph->numVertices;++i){
        if (!used[i]) continue;
        Node* next = graph->adjLists[i].head;
        while (next != NULL){
            if (used[next->vertex]){
                next = next->next;
                continue;
            }
            if (next->weight < minim){
                minim=next->weight;
                minimNode1 = i;
                minimNode2 = next->vertex;
            }
            next = next->next;
        }
    }
    used[minimNode2]=1;
    result[0] = minimNode1;
    result[1] = minimNode2;
    result[2] = minim;
    return result;
}

void prim(){
    //Find minimum spanning tree in O(m logm)
    int* res = malloc(sizeof(int)*3);
    int weight=0;
    printf("The minimum spanning tree contains the following edges:\n");
    used[0]  = 1;
    for (int i=0;i<graph->numVertices-1;++i){
        res = primHelper();
        weight+= res[2];
        printf("%d - %d\n", res[0],res[1]);
    }
    printf("The total weight is %d.",weight);
}
int main(){

    graph = createGraph(6);
    addEdge(graph,0,1,3);
    addEdge(graph,0,4,5);
    addEdge(graph,1,4,6);
    addEdge(graph,1,2,5);
    addEdge(graph,4,5,2);
    addEdge(graph,2,5,3);
    addEdge(graph,2,3,9);
    addEdge(graph,5,3,7);
    prim();
    //printGraph(graph);
    return 0;
}
