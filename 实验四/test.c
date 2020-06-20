#pragma GCC optimize(3)
#include "Sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* init(int _size){
    int* A = malloc(_size * sizeof(int));
    for(int i = 0; i < _size; i++){//10亿
        A[i] = (rand() % _size);
    }
    return A;
}
void Test(int length){
    srand((unsigned int) time(NULL));
    clock_t start = clock();
    int* A = init(length);
    start = clock();
    ShellSort(A,length);
    printf("希尔排序(%d个数)所用时间: %lu ms\n",length, clock() - start);
    free(A);
    A = init(length);
    start = clock();
    Two_Way_QuickSort(A,0,length - 1);
    printf("二路快排(%d个数)所用时间: %lu ms\n",length, clock() - start);
    free(A);
    A = init(length);
    start = clock();
    Three_Way_QuickSort(A,0,length - 1);
    printf("三路快排(%d个数)所用时间: %lu ms\n",length, clock() - start);
    free(A);
    A = init(length);
    start = clock();
    HeapSort(A,length);
    printf("堆排序(%d个数)所用时间: %lu ms\n",length, clock() - start);
    free(A);
}

int main(){
    for(int length = 1000; length <= 1000000000;length *= 10){
        Test(length);
        printf("-------------------------------\n");
    }
}
