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
}
void bfs(List** Graph,char v,char* vis){
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
List* Prim(List** Graph,char start,char* vis,int tot,int* sum){
    List* MST = (List*)calloc(1,sizeof(List));
    Pair p = {start,0};
    Push(p);
    for(int i = 0; i < tot; i ++){//每次循环都添加一个新的点进最小生成树中
        while(1){
            Pair pq_top = top();
            Pop();
            if(vis[pq_top.v] == 1) continue;//如果该顶点已经被添加进最小生成树了,则跳过
            vis[pq_top.v] = 1;//标记该顶点已被添加进最小生成树
            *sum += pq_top.w;//计算总权值
            insert(MST,pq_top.v,pq_top.w);//把该点添加到最小生成树中
            Node* tmp = Graph[pq_top.v]->head;
            while(tmp != NULL){//遍历与当前顶点相连的点,并把他们的边放入优先队列中
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
    int** adjacencyMatrix = Build_Adjacency_matrix();//建立邻接矩阵
    size_t len = malloc_usable_size(adjacencyMatrix[0]) / sizeof(int);//坑(malloc_usable_size 用于获取动态数组的长度,但在某些其他编译器上要使用_msize)
    printf("邻接矩阵:\n");
    for (int i = 0; i < len ; ++i) {//打印邻接矩阵
        for (int j = 0; j < len; ++j) {
            if(adjacencyMatrix[i][j] != 0)
                printf("%c - %c 的权值为%d  ", map[i], map[j], adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    getchar();//读掉回车
    List** Adjacency_list = Build_Adjacency_list();//建立邻接链表
    printf("邻接链表:\n");
    for (int i = 0; i < 128 ; ++i) {//打印邻接链表
        if(Adjacency_list[i]->head != NULL) {
            printList(Adjacency_list[i],(char)i);
        }
    }
    char vis[128] = {0};
    int index = 0;
    int i = 0;
    int tot = 0;
    while(i < 128){//随便找一个带边的点作为DFS起点
        if(Adjacency_list[i]->head != NULL){
            index = i;//记录下该顶点值
            tot ++;//顺便记录一下顶点总数,Prim要用到
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
    int Sum = 0;//记录生成的MST的总权值,来验证生成的树是否是最小生成树
    List* Minimum_Spinning_Tree = Prim(Adjacency_list,(char)index,vis,tot,&Sum);
    Node* tmp = Minimum_Spinning_Tree->head;
    while(tmp != NULL){
        printf("%c",tmp->v);
        tmp = tmp->next;
    }
    printf("\n生成的最小生成树的总权值为:%d",Sum);
    Delete_Adjacency_matrix(adjacencyMatrix);
    Delete_Adjacency_list(Adjacency_list);
    DeleteList(Minimum_Spinning_Tree);
}