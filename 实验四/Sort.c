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
    printf("ϣ������(100����)����ʱ��: %lu ms\n", clock() - start);
    Print(A);
    A = realloc(A,sizeof(int) * 200);
    for(int i = 0; i < 200; i++){
        A[i] = (rand() % 9800 + 200);
    }
    start = clock();
    Two_Way_QuickSort(A,0,199);
    ShellSort(A,200);
    printf("��·����(200����)����ʱ��: %lu ms\n", clock() - start);
    Print(A);
    A = realloc(A,sizeof(int) * 500);
    for(int i = 0; i < 500; i++){
        A[i] = (rand() % 9800 + 200);
    }
    start = clock();
    HeapSort(A,500);
    printf("������(500����)����ʱ��: %lu ms\n", clock() - start);
    Print(A);
    free(A);
}
