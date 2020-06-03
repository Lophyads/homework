#ifndef CLION_GRAPH_H
#define CLION_GRAPH_H
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
/* 因为图中的顶点是在(-128 ~ 127)的范围内,所以需要开一个256 * 256 的矩阵来储存可能出现的字符
 * 但如果能事先知道图的顶点数,那我们就能用一个很简单的方法把邻接矩阵从256 * 256 压缩为 V * V (V为图顶点数)
 * 方法: 用每个顶点第一次添加到邻接矩阵的次序(Rank)代替顶点本身的值储存进邻接矩阵中,因为只有V个顶点，所以(0 <= Rank <= V),我们就可以用一个V*V的矩阵进行储存
 * 首先创建一个Rank变量,初始为0
 * 然后创建一个rank数组,大小为256,初始为-1
 * Rank变量用于记录邻接矩阵中已存在的顶点数,邻接矩阵每添加一个新的顶点就把Rank+1
 * rank数组用于记录顶点对应的Rank
 * 每次把顶点添加到邻接矩阵时要先检查该顶点是否已经被添加过了
 * 如果已添加过(rank[v] != -1),那么直接使用rank[v]替代v存进邻接矩阵中
 * 若是新顶点(rank[v] == -1),那么更新rank[v] = Rank++;
 * 这样就可以建立一个V*V的邻接矩阵了
 * 但是因为邻接矩阵存的是顶点的Rank值而不是顶点值,所以要再用一个map数组保存Rank对应的顶点,这样在打印邻接矩阵时就可以通过map数组把Rank还原回顶点
 */
static int Rank = 0;
static char* map;
int** Build_Adjacency_matrix(){//邻接矩阵
    int VNum;//顶点数
    //printf("请输入图的顶点数:");
    printf("建立邻接矩阵,");
    printf("请在第一行输入图的顶点数:");
    printf("接下来的行输入两个顶点以及两点之间的权值(权值小于0时结束输入):\n");
    scanf("%d",&VNum);
    map = (char*)calloc(VNum,sizeof(char));
    memset(map,0,VNum * sizeof(char));
    int** Adjacency_matrix = (int**)malloc(sizeof(int *) * VNum);
    for(int i = 0; i < VNum; i++){
        Adjacency_matrix[i] = (int*)calloc(VNum, sizeof(int));
    }
    int rank[128];//记录字符对应的rank
    memset(rank, -1, 128 * sizeof(int));
    while(1){
        char x,y;
        int w;//权值
        getchar();//读回车
        scanf("%c%c%d",&x,&y,&w);
        if(w < 0) break;
        int v1, v2;
        if(rank[x] == -1) {
            rank[x] = Rank;
            map[Rank++] = x;
        }
        v1 = rank[x];
        if(rank[y] == -1){
            rank[y] = Rank;
            map[Rank++] = y;
        }
        v2 = rank[y];
        Adjacency_matrix[v1][v2] = Adjacency_matrix[v2][v1] = w;
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
    size_t len = malloc_usable_size(graph[0]) / sizeof(int);
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
#endif //CLION_GRAPH_H