#include <stdio.h>

int maxSubarraySumBad(int *array, int size);
int maxSubarraySumGood(int *array, int size);
int maxSubarraySumBest(int *array, int size);

void bubbleSort(int *array, int size);
void mergeSort(int *array, int left,int right);

int binarySearch(int *array, int x, int size);
int binarySearch2(int *array, int x, int size);

int main(){
    int test[] = {2,-2,3,4,-5,2,9,0,-1};
    mergeSort(test,0,9);
    int indeks = binarySearch2(test,4,9);
    for (int i=0; i<9; i++) printf("%d\n",test[i]);
    printf("%d",indeks);
    return 0;
}

int maxSubarraySumBad(int *array, int size){
    // O(n^3)
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
    //o(n^2)
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
    //o(n)
    int realMax=0;
    int runningMax=0;
    for (int i=0; i<size; i++){
        if ((runningMax + *(array+i)) > *(array+i)) runningMax += *(array+i);
        else runningMax = *(array+i);
        if (runningMax > realMax) realMax = runningMax;
    }
    return realMax;
}

void bubbleSort(int *array, int size){
    //o(n^2)
    int temp;
    for (int i =0;i<size;i++){
        for (int j= 0; j<size-1; j++){
            if ((array[j+1]) < (array[j])){
                temp = array[j+1];
                array[j+1] = array[j];
                array[j] = temp;
            }
        }
    }
}

void mergeSort(int *array, int left,int right){
    //o(n logn)
    if (left >= right-1) return;
    int mid = (right+left)/2;
    mergeSort(array,left,mid);
    mergeSort(array,mid,right);
    int aux[right-left]; 
    int Li = left;
    int Ri = mid;
    int i = 0;
    while (i<right-left){
        if (Ri == right){
            aux[i] = array[Li];
            Li++;
        }
        else if (Li == mid){
            aux[i] = array[Ri];
            Ri++;
        }
        else if (array[Li] < array[Ri]){
            aux[i] = array[Li];
            Li++;
        }
        else {
            aux[i] = array[Ri];
            Ri++;
        }
        i++;
    }
    for (int i=left;i<right;i++) array[i] = aux[i-left];

}

int binarySearch(int *array, int x, int size){
    //O(logn)
    int L=0;
    int R=size-1;
    int mid;
    while (L<=R){
        mid = (L+R)/2;
        if (array[mid] < x) L=mid+1;
        else R=mid-1;
    }
    if (array[mid] == x) return mid;
    else return -1;
}

int binarySearch2(int *array, int x, int size){
    //O(logn)
    int i=0;
    for (int jump=size/2;jump>=1;jump/=2){
        while (i+jump < size && array[i+jump]<=x) i+=jump;
    }
    if (array[i] == x) return i;
    else return -1;
}