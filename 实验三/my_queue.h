#ifndef ALGORITHM_MY_QUEUE_H
#define ALGORITHM_MY_QUEUE_H
#define Size 100
#define T char
static T my_queue[Size];
static int back = 0;
static int front = 0;
int is_empty(){
    return front == back;
}
int is_full(){
    return (back + 1) % Size == front;
}
int push(T element){
    if(is_full()){
        printf("队列已满\n");
        return 0;
    }
    my_queue[back++] = element;
    if(back == Size - 1){
        back = 0;
    }
    return 1;
}
T pop(){
    if(is_empty()){
        printf("队列为空\n");
        return (T)0;
    }
    T res = my_queue[front++];
    if(front == Size - 1) front = 0;
    return res;
}
int size(){
    return (back + Size - front) % Size;
}
#endif //ALGORITHM_MY_QUEUE_H