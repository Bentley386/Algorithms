#include <stdio.h>

void subsets(int n);
void subsets_aux(int k, int subs[], int *i, int n);
int main(){
    int n = 5;
    printf("%d",1<<n);
    return 0;
}

void subsets_aux(int k, int subs[], int *i, int n) {
    if (k==n){
        for (int l=0;l<n;l++) printf("%d ",subs[l]);
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

void subsets(int n){
    int subs[n];
    for (int i=0;i<n;i++) subs[i]=-1;
    int i=-1;
    subsets_aux(0,subs,&i,n);
}

void subsets2(int n){
    return;
}