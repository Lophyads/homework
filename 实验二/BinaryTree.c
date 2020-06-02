#include "BinaryTree.h"
TreeNode* BuildTree(char* str, int l, int r){//通过中序遍历建立二叉树
    if(l > r) return NULL;
    int mid = l + (r - l) / 2;
    TreeNode* node = (TreeNode*)calloc(1,sizeof(TreeNode));
    node->val = str[mid];
    node->left = BuildTree(str, l, mid - 1);
    node->right = BuildTree(str, mid + 1, r);
    return node;
}
void PostOrder(TreeNode* root){//后序遍历
    if(root == NULL) return;
    PostOrder(root->left);
    PostOrder(root->right);
    printf("%c",root->val);
}
void LevelOrder(TreeNode* root){//层次遍历
    push(root);
    while(!is_empty()){
        TreeNode* top = pop();
        //把当前节点的左右儿子(若不为NULL)压入队列中
        if(top->left) push(top->left);
        if(top->right) push(top->right);
        printf("%c",top->val);//打印当前节点
    }
}
int depth(TreeNode* root){//求树的深度
    if(root == NULL) return 0;
    int l = depth(root->left);
    int r = depth(root->right);
    //#define max(x,y) x > y ? x : y
    int res = max(l, r) + 1;
    return res;
}
void Travel(TreeNode* node){//先序遍历获得树中的叶子节点和非叶子节点
    if(node == NULL) return;
    if(node->left == NULL && node->right == NULL){//判断为叶子节点
        Leaf[leaf_num++] = node;
        return;
    }
    Not_Leaf[not_leaf_num++] = node;
    Travel(node->left);
    Travel(node->right);
}
int main(){
    char* s = "ABCDEFGHIJK";
    TreeNode* root = BuildTree(s, 0, (int)strlen(s));
    printf("后序遍历序列为: ");
    PostOrder(root);
    printf("\n");
    printf("层次遍历序列为: ");
    LevelOrder(root);
    printf("\n");
    printf("树的深度为%d\n",depth(root));
    Travel(root);
    printf("叶子节点有: ");
    for(int i = 0; i < leaf_num; i++){
        printf("%c ",Leaf[i]->val);
    }
    printf("\n");
    printf("非叶儿节点有: ");
    for (int j = 0; j < not_leaf_num; ++j) {
        printf("%c ",Not_Leaf[j]->val);
    }
    DeleteTree(root);
}