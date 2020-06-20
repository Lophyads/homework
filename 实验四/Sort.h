#ifndef ALGORITHM_SORT_H
#define ALGORITHM_SORT_H
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
void swap(int* a, int* b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void ShellSort(int* arr,int len){
    for(int grep = len / 2; grep > 0; grep /= 2){
        for(int i = 0 ; i + grep < len; i++){
            int j = i + grep;
            int tmp = arr[j];
            while(j >= grep && arr[j - grep] > tmp){
                arr[j] = arr[j - grep];
                j -= grep;
            }
            arr[j] = tmp;
        }
    }
}
int Two_Way_Partition(int* arr, int lo, int hi){
    /*此法选取随机枢纽元,可以提升算法稳定性
     *int pos = rand() % (hi - lo + 1) + lo;
     *swap(&arr[pos],&arr[lo]);
    */
    int tmp = arr[lo];//以arr[lo]为枢纽元
    while(lo < hi){
        while(lo < hi && arr[hi] >= tmp) hi--;//从右往左找到第一个比枢纽元小的数
        arr[lo] = arr[hi];
        while(lo < hi && arr[lo] <= tmp) lo++;//从左往右找到第一个比枢纽元大的数
        arr[hi] = arr[lo];
    }
    arr[lo] = tmp;
    return lo;
}
void Two_Way_QuickSort(int* arr,int lo, int hi){
    if(hi <= lo) return;
    int mid = Two_Way_Partition(arr,lo,hi);
    Two_Way_QuickSort(arr, lo, mid - 1);
    Two_Way_QuickSort(arr, mid + 1, hi);
}
void Three_Way_Partition(int* arr, int lo, int hi, int* i, int* j){
    if(hi - lo <= 1){//对两个元素进行特判
        if(arr[hi] < arr[lo])
            swap(&arr[lo], &arr[hi]);
        *i = lo;
        *j = hi;
        return;
    }
    int pivot = arr[hi];//以arr[hi]作为中位数
    int cur = lo;
    while(cur <= hi){
        if(arr[cur] < pivot)
            swap(&arr[cur++],&arr[lo++]);
        else if(arr[cur] > pivot)
            swap(&arr[cur],&arr[hi--]);
        else cur++;
    }
    *i = lo - 1;
    *j = cur;
}
void Three_Way_QuickSort(int* arr,int lo, int hi){
    if(lo >= hi) return;
    int i = 0, j = 0;
    Three_Way_Partition(arr, lo, hi, &i, &j);
    //三路快排把数组切分为 (arr[lo] ~ arr[i]) < (arr[i + 1] ~ arr[j - 1]) < (arr[j] ~ arr[hi]) 三个区间
    Three_Way_QuickSort(arr, lo, i);
    Three_Way_QuickSort(arr, j, hi - 1);
}
void HeapAdjust(int* arr, int root, int len){
    for (int i = root * 2 + 1; i < len; i = i * 2 + 1) {
        if(i < len - 1 && arr[i + 1] > arr[i]) i++;
        if(arr[root] < arr[i]){
            swap(&arr[root],&arr[i]);
            /*int tmp = arr[root];
            arr[root] = arr[i];
            arr[i] = tmp;*/
            root = i;
        }
        else break;
    }
}
void HeapSort(int* arr, int len){
    //先自底向上建堆
    for(int i = (len - 1) / 2; i >= 0; i --)
        HeapAdjust(arr,i,len);
    while(--len){
        swap(&arr[0], &arr[len]);
        /*int tmp = arr[0];
        arr[0] = arr[len];
        arr[len] = tmp;*/
        HeapAdjust(arr,0,len);//自顶向下建堆
    }
}
void Print(int* arr){
    int len = (int) (_msize(arr) / sizeof(int));
    for (int i = 0; i < len; ++i) {
        printf(" %d ",arr[i]);
        if((i + 1) % 10 == 0) printf("\n");
    }
    printf("\n");
}
#endif //ALGORITHM_SORT_H
