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
    /*�˷�ѡȡ�����ŦԪ,���������㷨�ȶ���
     *int pos = rand() % (hi - lo + 1) + lo;
     *swap(&arr[pos],&arr[lo]);
    */
    int tmp = arr[lo];//��arr[lo]Ϊ��ŦԪ
    while(lo < hi){
        while(lo < hi && arr[hi] >= tmp) hi--;//���������ҵ���һ������ŦԪС����
        arr[lo] = arr[hi];
        while(lo < hi && arr[lo] <= tmp) lo++;//���������ҵ���һ������ŦԪ�����
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
    if(hi - lo <= 1){//������Ԫ�ؽ�������
        if(arr[hi] < arr[lo])
            swap(&arr[lo], &arr[hi]);
        *i = lo;
        *j = hi;
        return;
    }
    int pivot = arr[hi];//��arr[hi]��Ϊ��λ��
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
    //��·���Ű������з�Ϊ (arr[lo] ~ arr[i]) < (arr[i + 1] ~ arr[j - 1]) < (arr[j] ~ arr[hi]) ��������
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
    //���Ե����Ͻ���
    for(int i = (len - 1) / 2; i >= 0; i --)
        HeapAdjust(arr,i,len);
    while(--len){
        swap(&arr[0], &arr[len]);
        /*int tmp = arr[0];
        arr[0] = arr[len];
        arr[len] = tmp;*/
        HeapAdjust(arr,0,len);//�Զ����½���
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
