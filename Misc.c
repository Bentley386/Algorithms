#include <stdio.h>

void subsets(int n); //Find all subsets of a set with n elements using recursion.
void subsets_aux(int k, int subs[], int *i, int n);

void subsets2(int); //Find all subsets of a set with n elements using bit operations.

void permutation(int n); //Find all permutations of a set with n elements using recursion.
void permutation_aux(int perm[], int *i, int chosen[],int n);

void huffman(); //TO DO 

int main(){
    permutation(3);
    return 0;
}

void permutation(int n){
    //Prints all permutation of a set {1,2,3..,n}

    int i=0;
    int chosen[n],perm[n];
    for (int i=0;i<n;i++) chosen[i]=0;
    permutation_aux(perm,&i,chosen,n);
}

void permutation_aux(int perm[], int*i,int chosen[], int n){
    //Auxiliar recursive function for permutation(n)

    if (*i==n){
        for (int l=0;l<n;l++) printf("%d ", perm[l]);
        printf("\n");
    }
    for (int l=0;l<n;l++){
        if (chosen[l]) continue;
        chosen[l] = 1;
        perm[*i] = l;
        *i = *i + 1;
        permutation_aux(perm,i,chosen,n);
        chosen[l] = 0;
        *i = *i - 1;
    }
}


void subsets(int n){
    //Print all subsets of a set {1,2,3...,n}

    int subs[n];
    for (int i=0;i<n;i++) subs[i]=-1;
    int i=-1;
    subsets_aux(0,subs,&i,n);
}

void subsets_aux(int k, int subs[], int *i, int n) {
    //Auxiliar recursive function  for subsets(n)

    if (k==n){
        for (int l=0;l<n;l++) {
            if (subs[l] != -1) printf("%d ",subs[l]);
            //else printf(" ");
        }
        printf("\n");
    }
    else{ 
        subsets_aux(k+1,subs,i,n);
        *i = *i + 1;
        subs[*i]=k;
        subsets_aux(k+1,subs,i,n);
        subs[*i]=-1;
        *i = *i - 1;
    }
}


void subsets2(int n){
    //Print all subsets of the set {1,2,3,...,n}
    for (int i=0;i<(1<<n);i++){
        for(int j=0;j<n;j++){
            if (i&(1<<j)) printf("%d ",j);
        }
        printf("\n");
    }
}