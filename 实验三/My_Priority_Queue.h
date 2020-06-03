#ifndef CLION_MY_PRIORITY_QUEUE_H
#define CLION_MY_PRIORITY_QUEUE_H
typedef struct {
    char v;//顶点
    int w;//权值
}Pair ;
#define type Pair
static int PQsize = 100000;
static int Front = 0;
static int Back = 0;
static type Priority_queue[100000];
int empty(){ return Front == Back;}
int full(){ return Back == PQsize;}
int pq_size(){ return Back - Front;}
type top(){return Priority_queue[Front];}
void swap(type* x, type* y){
    type tmp = *x;
    *x = *y;
    *y = tmp;
}
void HeapAdjust(type* arr,int root,int step,int len){//调整顶堆,step为偏移量,偏移后的坐标才是正确的坐标
    for(int cur = root * 2 + 1; cur < len; cur = cur * 2 + 1){
        if(cur < len - 1 && arr[cur + step].w > arr[cur + step + 1].w)
            cur ++;
        if(arr[cur + step].w < arr[root + step].w){
            swap(&arr[cur + step], &arr[root + step]);
            root = cur;
        }
        else break;
    }
}
int Push(type element){
    if(full()) return 0;//队列已满,需要扩容
    Priority_queue[Back++] = element;
    //自底向上调整顶堆
    for(int root = (Back - Front - 2) / 2; root > 0; root = (root - 1) / 2)//root为插入节点的父节点,(root - 1) / 2得到root的父节点
        HeapAdjust(Priority_queue,root,Front,pq_size());
    HeapAdjust(Priority_queue,0,Front,pq_size());
    return 1;
}
int Pop(){
    if(empty()) return 0;
    Front++;
    //自顶向下调整顶堆
    HeapAdjust(Priority_queue,0,Front,pq_size());
    return 1;
}
#endif //CLION_MY_PRIORITY_QUEUE_H