#ifndef ALGORITHM_MY_PRIORITY_QUEUE_H
#define ALGORITHM_MY_PRIORITY_QUEUE_H
typedef struct {
    char v;//顶点
    int w;//权值
}Pair ;
#define type Pair
#define Psize  100000
static int Front = 0;
static int Back = 0;
static type Priority_queue[Psize];
void swap(type* x, type* y){
    type tmp = *x;
    *x = *y;
    *y = tmp;
}
void HeapAdjust(type* arr,int root,int step,int len){//建立大顶堆,step为偏移量,偏移后的坐标才是正确的坐标
    for(int cur = root * 2 + 1; cur < len; cur = cur * 2 + 1){
        if(cur < len - 1 && arr[cur + step].w < arr[cur + step + 1].w)
            cur ++;
        if(arr[cur + step].w > arr[root + step].w){
            swap(&arr[cur + step], &arr[root + step]);
            root = cur;
        }
        else break;
    }
}
void HeapSort(type* arr,int l,int r){
    for(int i = (r - 1 - l) / 2; i >= 0; i-- ) HeapAdjust(arr,i,l,r - l);//初始化顶堆
    while(--r > l){
        swap(&arr[l], &arr[r]);
        HeapAdjust(arr,0,l,r - l);
    }
}
int empty(){
    return Front == Back;
}
int Push(type element){
    Priority_queue[Back++] = element;
    HeapSort(Priority_queue,Front,Back);
    return 1;
}
int Pop(){
    if(empty()){
        printf("队列为空\n");
        return 0;
    }
    Front++;
    return 1;
}
type top(){
    return Priority_queue[Front];
}
int pq_size(){
return Back - Front;
}
#endif //ALGORITHM_MY_PRIORITY_QUEUE_H