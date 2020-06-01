#ifndef ALGORITHM_BINARYTREE_H
#define ALGORITHM_BINARYTREE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(x,y) x > y ? x : y
typedef struct treenode{
    char val;
    struct treenode* left;
    struct treenode* right;
}TreeNode;
#define size 100
static TreeNode* queue[size];
static TreeNode* Leaf[size];
static TreeNode* Not_Leaf[size];
static int leaf_num = 0;
static int not_leaf_num = 0;
static int front = 0;
static int back = 0;
int is_empty(){
    return front == back;
}
int is_full(){
    return (back + 1) % size == front;
}
int push(TreeNode* node){
    if(is_full()){
        printf("队列已满\n");
        return 0;
    }
    queue[++back] = node;
    if(back == size - 1){
        back = 0;
    }
    return 1;
}
TreeNode* pop(){
    if(is_empty()){
        printf("队列为空\n");
        return NULL;
    }
    TreeNode* res = queue[++front];
    if(front == size - 1) front = 0;
    return res;
}
void DeleteTree(TreeNode* node){
    if(node == NULL) return;
    DeleteTree(node->left);
    DeleteTree(node->right);
    free(node);
}
#endif //ALGORITHM_BINARYTREE_H