#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define size 101
static char Queue[size];
static int front = 0;
static int back = 0;
void init(){
    memset(Queue, 0, size);
}
int empty(){
    if(front == back) return 1;//为空
    return 0;//不为空
}
int push(char val){
    if((back + 1) % size == front){
        printf("队列已满，入队失败\n");
        return 0;
    }
    Queue[++back] = val;
    return 1;
}
char pop(){
    if(empty()){
        printf("队列为空\n");
        system("pause");
    }
    return Queue[++front];
}
int main(){
    init();
    char ch;
    while(1){
        printf("请输入元素,结束输入#:");
        while((ch = getchar()) != '\n' && ch != '#') {
            push(ch);
        }
        if(ch == '#') break;
    }
    while(empty() == 0){
        printf("%c",pop());
    }
    return 0;
}