#include <stdio.h>
#include <stdlib.h>

int* subarray_sum(int input[], int n, int x); //Find a subarray that sums to a given number.

int* TwoSum(int input[],int n, int x); //Find two elements of an array that sum up to a given number

int main(){
    int *res = malloc(sizeof(int)*2);
    int in[] = {1,4,5,6,7,9,9,10};
    res  = TwoSum(in,8,12);
    printf("%d %d",res[0],res[1]);
    return 0;
}

int cmp(const void* a, const void* b){ //Comparison function for qsort
    return (*((int*)a)-*((int*)b));
}

int* TwoSum(int input[], int n, int x){
    //2SUM: Find two elements of array input with size n, that sum to x or return {-1,-1} if that is not possible.

    static int result[] = {-1,-1};
    qsort(input,n,sizeof(int),cmp);
    int sum=0,r=n-1;
    for (int l=0;l<n;l++){
        while(r>=l){
            sum = input[l]+input[r];
            if(sum<=x){
                break;
            }
            r--;
        }
        if (sum==x){
            result[0]=l;
            result[1]=r;
            break;
        }
        if(r<l) break;
        r++;
    }
    return result;
}
int* subarray_sum(int input[],int n, int x){
    //Find a subarray [l,r] of array input that has a subarray sum of x. Returns [-1,1] if that is impossible.

    static int result[] = {-1,-1};
    int sum=0,r=0;
    for(int l=0;l<n;l++){
        while(r<n){
            sum+=input[r];
            if(sum>x) {
                sum-=input[r];
                break;
            }
            r++;
        }
        if (sum==x){
            result[0]=l;
            result[1]=r;
            break;
        }
        sum-=input[l];
    }
    return result;
}