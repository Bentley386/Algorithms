#include <stdio.h>

int maxSubarraySumBad(int *array, int size);
int maxSubarraySumGood(int *array, int size);
int maxSubarraySumBest(int *array, int size);

int main(){
    int test[] = {-1,2,4,-3,5,2,-5,2};
    printf("%d",maxSubarraySumBest(test,8));
    return 0;
}

int maxSubarraySumBad(int *array, int size){
    int max=0;
    int sum;
    for (int i=0; i<size;i++){
        for (int j=i; j<size; j++){
            sum=0;
            for (int k=i; k<=j;k++){
                sum+= *(array+k);
            }
            if (sum > max) max=sum;

        }
    }
    return max;
}

int maxSubarraySumGood(int *array, int size){
    int max=0;
    int sum;
    for (int i=0; i<size;i++){
        sum = 0;
        for (int j=i; j<size; j++){
            sum+=*(array+j);
            if (sum>max) max=sum;
        }
    }
    return max;   
}

int maxSubarraySumBest(int *array, int size){
    int realMax=0;
    int runningMax=0;
    for (int i=0; i<size; i++){
        if ((runningMax + *(array+i)) > *(array+i)) runningMax += *(array+i);
        else runningMax = *(array+i);
        if (runningMax > realMax) realMax = runningMax;
    }
    return realMax;
}