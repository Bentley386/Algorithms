#include <stdio.h>
#include <stdlib.h>

#define N 100000

int maxSubarraySumBad(int *array, int size); //Find maximum subarray sum
int maxSubarraySumGood(int *array, int size);
int maxSubarraySumBest(int *array, int size);

void bubbleSort(int *array, int size);
void mergeSort(int *array, int left,int right);

int * countingSort(int *array, int size, int maxEl); //Sort an array with non negative bounded elements.

int binarySearch(int *array, int x, int size);
int binarySearch2(int *array, int x, int size);

int main(){
    int test[] = {2,6,3,4,12,2,9,0,15};
    int* result = malloc(sizeof(int)*N); 
    result = countingSort(test,9,100);
    for (int i=0; i<9; i++) printf("%d\n",*(result+i));
    return 0;
}

int maxSubarraySumBad(int *array, int size){
    // Find maximum subarray sum in O(n^3)

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
    // Find maximum subarray sum in O(n^2)

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
    //Find maximum subarray sum in O(n)

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
    //Sort an array in place in O(n^2)

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
    //Sort an array in place in O(n logn). Initial call is with left=0,right=size-1

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

int* countingSort(int *array, int size, int maxEl){
    //Sort an array, with integer elements in [0,maxEl] in O(n).

    int Count[maxEl];
    for (int i=0;i<maxEl;i++) Count[i]=0;
    for (int i=0;i<size;i++){
        Count[array[i]]++;
    }
    static int result[N]; 
    int i=0;
    for (int j=0;j<maxEl;j++){
        if (!Count[j]) continue;
        while(Count[j]--) {
            *(result+i) = j;
            i++;
        }
    }
    return result;
}

int binarySearch(int *array, int x, int size){
    //Find an element x in a sorted array in O(logn).

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
    //Find an element x in a sorted array in O(logn).

    int i=0;
    for (int jump=size/2;jump>=1;jump/=2){
        while (i+jump < size && array[i+jump]<=x) i+=jump;
    }
    if (array[i] == x) return i;
    else return -1;
}