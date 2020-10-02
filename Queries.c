#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10000

int* staticSumPrepare(int*,int); //Prepare an array for sum queries.
int staticSumQuery(int*,int,int,int); //Perform a sum query.

void staticMinPrepare(int**,int*,int); //Prepare an array for min queries.
int staticMinQuery(int**,int,int,int); //Perform a min query.

int* fenwickTreePrepare(int*, int); 
void updateFenwick(int*,int,int,int); //Dynamic sum query supporting efficient array updates.
int processSum(int*, int, int, int);

int newSize(int);
int* segmentTreePrepare(int*,int);
void updateSegment(int*, int, int, int); //Another structure supporting dynamic queries.
int processSum2(int*, int, int, int);

int min(int a,int b){
    if (a<b) return a;
    return b;
}

int main(){
    int test[] = {5,8,6,3,2,7,2,6};
    int* seggy = segmentTreePrepare(test,8);
    updateSegment(seggy,8,4,2);
    int res = processSum2(seggy,8,2,7);

    printf("%d",newSize(7));
    return 0;
}

void updateSegment(int* segment, int size, int pos, int x){
    //add x to pos-th element in segment tree.
    
    pos += size;
    segment[pos] += x;
    for (pos /=2; pos>=1; pos/=2) segment[pos] = segment[2*pos]+segment[2*pos+1];
}

int processSum2(int* segment, int size, int a, int b){
    //Process a sum query

    a+=size;
    b+=size;
    int sum=0;
    while (a<=b){
        if (a%2 == 1) sum+= segment[a++];
        if (b%2 == 0) sum+= segment[b--];
        a/=2;
        b/=2;
    }
    return sum;
}

int* segmentTreePrepare(int* original, int size){
    //Prepare a segment tree for sum/min/max query

    static int result[N];
    for (int i=size;i<2*size;i++){
        result[i] = original[i-size];
    }
    for (int i=size-1;i>=1;i--){
        result[i] = result[2*i]+result[2*i+1];
    }
    return result;
}



int newSize(int old){
    //Calculate the nearest bigger number than old that is a power of two. 
    int size=old;
    while (size != (size&(-size))) size++;
    return size;
}


void updateFenwick(int* fenwick, int size, int pos, int x){
    //Update the fenwick tree by with the addition of x to pos-th element.

    while (pos <= size){
        fenwick[pos] += x;
        pos += pos&-pos;
    }
}

int processSum(int* fenwick, int size, int a, int b){
    //Process a sum query.

    if (a==1){
        int res=0;
        while (b >= 1){
            res += fenwick[b];
            b -= b&-b;
        }
        return res;
    }
    return processSum(fenwick,size,1,b)-processSum(fenwick,size,1,a-1);
}

int* fenwickTreePrepare(int* original, int size){
    //Create a fenwick (binary indexed) tree for dynamic sum queries of original array.

    static int result[N];
    int p,sum;
    for (int i=1;i<=size;i++){
        p = i&(-i);
        sum=0;
        for (int j=i-p;j<=i-1;j++) sum+= original[j];
        result[i]=sum;
    }
    return result;
}

void staticMinPrepare(int** prefix, int* original,int size){
    //Prepare an auxiliary array for min queries.

    for (int i=0;i<size;i++) prefix[i][1] = original[i];
    int size2 = log2(size);
    for (int i = 1; i <= size2; i++){
        int jump = pow(2,i);
        for (int j=0;j<size;j++){
            if (j+jump-1 >= size) break;
            int w=jump/2;
            prefix[j][jump] = min(prefix[j][w],prefix[j+w][jump-w]);
        }
    }
    

}

int staticMinQuery(int** premade, int size, int a, int b){
    //Find a min element in a subarray [a,b].

    int k = log2(b-a+1);
    return min(premade[a][k],premade[b-k+1][k]);
}

int* staticSumPrepare(int* original, int size){
    //Prepare prefix array for sum queries for array original. 

    static int result[N];
    result[0] = original[0];
    for (int i=1;i<size;i++){
        result[i] = result[i-1]+original[i];
    }
    return result;
}

int staticSumQuery(int* prefix, int size, int a, int b){
    //Perform a sum query. Get subarray sum of a range [a,b] given a prefix array.

    if (a==0) return prefix[b];
    else return prefix[b]-prefix[a-1];
}