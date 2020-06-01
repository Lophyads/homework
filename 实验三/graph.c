#include "graph.h"
#include "my_queue.h"
#include "My_Priority_Queue.h"
void dfs(List** Graph,Node* node,char* vis){;
    Node* cur = node;
    while(cur != NULL){
        if(vis[cur->v] == 0){ //该节点未被遍历
            printf("%c",cur->v);
            vis[cur->v] = 1;
            dfs(Graph,Graph[cur->v]->head, vis);
        }
        cur = cur->next;
    }
}void bfs(List** Graph,char v,char* vis){
    push(v);
    vis[v] = 1;
    int cnt = 1;
    while(!is_empty()){
        int q_size = size();
        printf("\n第%d层:",cnt++);
        while(q_size--){
            T qf = pop();
            printf("%c",qf);
            Node* tmp = Graph[qf]->head;
            while(tmp != NULL){
                if(vis[tmp->v] == 0) {
                    push(tmp->v);
                    vis[tmp->v] = 1;
                }
                tmp = tmp->next;
            }
        }
    }
}
List* Prim(List** Graph,char start,char* vis,int tot){
    List* MST = (List*)calloc(1,sizeof(List));
    Pair p = {start,0};
    Push(p);
    for(int i = 0; i < tot; i ++){//每次循环都添加一个新的点进最小生成树中
        while(1){
            Pair pq_top = top();
            Pop();
            if(vis[pq_top.v] == 1) continue;
            vis[pq_top.v] = 1;
            insert(MST,pq_top.v,pq_top.w);//把该点添加到最小生成树中
            Node* tmp = Graph[pq_top.v]->head;
            while(tmp != NULL){
                if(vis[tmp->v] == 0){
                    Pair t = {tmp->v,tmp->w};
                    Push(t);
                }
                tmp = tmp->next;
            }
            break;
        }
    }
    return MST;
}
int main(){
    int** adjacencyMatrix = Build_Adjacency_matrix();
    size_t len = malloc_usable_size(adjacencyMatrix[0]) / sizeof(int);//坑
    printf("邻接矩阵:\n");
    for (int i = 0; i < len ; ++i) {
        for (int j = 0; j < len; ++j) {
            if(adjacencyMatrix[i][j] != 0)
            printf("%d - %d 的权值为%d  ", i, j, adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    getchar();
    List** Adjacency_list = Build_Adjacency_list();
    printf("邻接链表:\n");
    for (int i = 0; i < 128 ; ++i) {
            if(Adjacency_list[i]->head != NULL) {
                printList(Adjacency_list[i],(char)i);
            }
    }
    char vis[128] = {0};
    //memset(vis,0,128);
    int index = 0;
    int i = 0;
    int tot = 0;
    while(i < 128){//随便找带边的点作为DFS起点
        if(Adjacency_list[i]->head != NULL){
            index = i;
            tot ++;//顺便记录一下顶点总数，Prim要用到
        }
        i++;
    }
    printf("DFS序列:");
    dfs(Adjacency_list,Adjacency_list[index]->head,vis);
    memset(vis,0,sizeof(vis));//重新初始化
    printf("\nBFS序列:");
    bfs(Adjacency_list,(char)index,vis);
    memset(vis,0,sizeof(vis));
    printf("\n最小生成树:");
    List* Minimum_Spinning_Tree = Prim(Adjacency_list,(char)index,vis,tot);
    Node* tmp = Minimum_Spinning_Tree->head;
    while(tmp != NULL){
        printf("%c",tmp->v);
        tmp = tmp->next;
    }
    Delete_Adjacency_matrix(adjacencyMatrix);
    Delete_Adjacency_list(Adjacency_list);
    DeleteList(Minimum_Spinning_Tree);
}