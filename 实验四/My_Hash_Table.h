#ifndef ALGORITHM_MY_HASH_TABLE_H
#define ALGORITHM_MY_HASH_TABLE_H
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define T int
typedef struct node{
    T val;
    struct node* next;
}Node;
#define Type Node
static int P = 17;
int h(T key){
    return key % P;
}
Type** init(int X){//初始化类型为type,X大小的二维数组
    Type** array = (Type**)calloc(X,sizeof(Type*));
    if(array == NULL) return NULL;//空间不足,分配失败
    for(int i = 0; i < X; i ++) {
        array[i] = (Type *) calloc(1, sizeof(Type));
        array[i]->val = -1;
    }
    return array;
}
void insert(Type** array, T key){
    int hash = h(key);
    Type* tail = array[hash];
    if(tail->val == -1){
        tail->val = key;
        return;
    }
    while(tail->next != NULL) tail = tail->next;
    tail->next = (Type*)calloc(1,sizeof(Type));
    tail->next->val = key;
}
void Print_Hash_Table(Type** array){
    int len = _msize(array);
    for(int i = 0; i < len; i++){
        printf("桶 %d:  ",i);
        Type* cur = array[i];
        if(cur->val == -1){
            printf("该桶为空!\n");
            return;
        }
        while(cur != NULL) {
            printf(" %d ", cur->val);
            cur = cur->next;
        }
        printf("\n");
    }
}
void Delete_Array(Type** array){
    int len = _msize(array);
    while(len --){
        free(array[len]);
    }
    free(array);
}
#endif //ALGORITHM_MY_HASH_TABLE_H
