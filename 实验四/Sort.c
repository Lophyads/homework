#include "Sort.h"
#include <time.h>
#include <stdlib.h>
int main(){
    srand((unsigned int) time(NULL));
    int* A = (int*)calloc(100, sizeof(int));
    for(int i = 0; i < 100; i++){
        A[i] = (rand()%800 + 200);
    }
    clock_t start = clock();
    ShellSort(A,100);
    printf("希尔排序(100个数)所用时间: %lu ms\n", clock() - start);
    Print(A);
    A = realloc(A,sizeof(int) * 200);
    for(int i = 0; i < 200; i++){
        A[i] = (rand() % 9800 + 200);
    }
    start = clock();
    Two_Way_QuickSort(A,0,199);
    ShellSort(A,200);
    printf("二路快排(200个数)所用时间: %lu ms\n", clock() - start);
    Print(A);
    A = realloc(A,sizeof(int) * 500);
    for(int i = 0; i < 500; i++){
        A[i] = (rand() % 9800 + 200);
    }
    start = clock();
    HeapSort(A,500);
    printf("堆排序(500个数)所用时间: %lu ms\n", clock() - start);
    Print(A);
    free(A);
}
