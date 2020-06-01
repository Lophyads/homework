#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct node {
    char v;//顶点
    int w;//权值
    struct node* next;
}Node;
typedef struct list {
    Node* head;
    Node* tail;
}List;
Node* insert(List* ListNode, char v, int w) {
    if(ListNode->head == NULL){
        Node* node = (Node*)malloc(sizeof(Node));
        node->v = v;
        node->w = w;
        node->next = NULL;
        ListNode->head = node;
        ListNode->tail = ListNode->head;
        return ListNode->head;
    }
    Node* node = (Node*)malloc(sizeof(Node));
    node->v = v;
    node->w = w;
    node->next = NULL;
    ListNode->tail->next = node;
    ListNode->tail = node;
    return ListNode->tail;
}
List** Build_Adjacency_list(){
    List** Adjacency_list = (List**)calloc(128,sizeof(List*));
    for(int i = 0;i < 128; i ++){
        Adjacency_list[i] = (List*)calloc(1,sizeof(List));
        Adjacency_list[i]->head = NULL;
    }//初始化
    printf("建立邻接链表,");
    printf("请输入两个顶点以及两点之间的权值(权值小于0时结束输入):\n");
    while(1){
        char x,y;
        int w;//权值
        scanf("%c%c%d",&x,&y,&w);
        getchar();//坑!!!
        if(w < 0) break;
        insert(Adjacency_list[x], y, w);
        insert(Adjacency_list[y], x, w);
    }
    return Adjacency_list;
}
int get_hash_num(char ch, int VNum, int* hash,int* seen){
    int hash_num = ch % VNum;//取模保证(0 <= hash_num <= num)
    while(seen[hash_num] != -1){//找到一个未被使用的hash_num
        hash_num = (hash_num + 1) % VNum;
    }
    seen[hash_num] = 1;
    hash[ch] = hash_num;
    return hash_num;
}
int** Build_Adjacency_matrix(){//邻接矩阵
    int VNum;//顶点数
    //printf("请输入图的顶点数:");
    printf("建立邻接矩阵,");
    printf("请在第一行输入图的顶点数:");
    printf("接下来的行输入两个顶点以及两点之间的权值(权值小于0时结束输入):\n");
    scanf("%d",&VNum);
    int** Adjacency_matrix = (int**)malloc(sizeof(int *) * VNum);
    for(int i = 0; i < VNum; i++){
        Adjacency_matrix[i] = (int*)calloc(VNum, sizeof(int));
    }
    int* seen = (int*) malloc(sizeof(int) * VNum);//用于检查某个hash_num是否被使用了
    memset(seen, -1, VNum * sizeof(int));
    int hash[128];//记录字符对应的hash_num
    memset(hash, -1, 128 * sizeof(int));//坑!!!
    while(1){
        char x,y;
        int w;//权值
        getchar();//读回车
        scanf("%c%c%d",&x,&y,&w);
        //printf("%d",w);
        //getchar();//坑!!!
        if(w < 0) break;
        int v1, v2;
        if(hash[x] == -1)
            hash[x] = get_hash_num(x,VNum,hash,seen);
        v1 = hash[x];
        if(hash[y] == -1)
            hash[y] = get_hash_num(y,VNum,hash,seen);
        v2 = hash[y];
        Adjacency_matrix[v1][v2] = Adjacency_matrix[v2][v1] = w;
        //printf("%d%d",v1,v2);
    }
    return Adjacency_matrix;
}
void printList(List* ListNode,char c) {
    Node* node = ListNode->head;
    if (node == NULL) return;
    while (node != NULL) {
        printf("%c - %c 的权值为: %d  ",c,node->v,node->w);
        node = node->next;
    }
    printf("\n");
}
void Delete_Adjacency_matrix(int** graph){
    size_t len = _msize(graph[0]) / sizeof(int);
    for(size_t i = 0; i < len; i++){
        free(graph[i]);
    }
    free(graph);
}
void DeleteList(List* list){
    Node* tmp = list->head;
    while(tmp != NULL){
        Node* t = tmp;
        tmp = tmp->next;
        free(t);
    }
    free(list);
}
void Delete_Adjacency_list(List** list){
    for(int i = 0; i < 128; i++){
        DeleteList(list[i]);
    }
}
#endif //ALGORITHM_GRAPH_H