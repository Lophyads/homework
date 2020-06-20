#include "My_Hash_Table.h"
void search(Type** array,int k){
    int t = h(k);
    Type* tmp = array[t];
    while(tmp != NULL){
        if(tmp->val == k){
            printf("已找到\n");
            return ;
        }
        tmp = tmp->next;
    }
    printf("找不到\n");
}
void erase(Type** array,int num){
    int k = h(num);
    Type* tmp = array[k];
    if(tmp->val == num){
        Type* t = tmp;
        if(t->next != NULL){
            array[num] = t;
            free(t);
        }
        else array[num]->val = -1;
    }
    while(tmp->next != NULL){
        if(tmp->next->val == num){
            Type* t = tmp->next;
            tmp->next = tmp->next->next;
            free(t);
        }
        tmp = tmp->next;
    }
    if(tmp->val == num)
        free(tmp);
}
int main(){
    int A[50];
    int num = 20;
    for(int i = 0; i < 50; i++){
        A[i] = num;
        num += 13;
    }
    Type** array = init(20);
    for(int i = 0; i < 50; i ++){
        insert(array,A[i]);
    }
    Print_Hash_Table(array);
    Delete_Array(array);
    return 0;
}
