#ifndef ALGORITHM_LIST_H
#define ALGORITHM_LIST_H
typedef struct node {
    int coefficient;//系数
    int index;//指数
    struct node* next;
}Node;
typedef struct list {
    Node* head;
    Node* tail;
}List;
Node* insert(List* ListNode, int coefficient, int index) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->coefficient = coefficient;
    node->index = index;
    node->next = NULL;
    ListNode->tail->next = node;
    ListNode->tail = node;
    return ListNode->tail;
}
void printList(List* ListNode) {
    Node* node = ListNode->head->next;
    if (node == NULL) return;
    while (node->next != NULL) {
        printf("%dx^%d + ", node->coefficient, node->index);
        node = node->next;
    }
    printf("%dx^%d", node->coefficient, node->index);
    printf("\n");
}
void DeleteList(List* list){
    Node* tmp = list->head;
    while(tmp->next != NULL){
        Node* nxt = tmp->next;
        free(tmp);
        tmp = nxt;
    }
    free(list->tail);
    free(list);
}
#endif //ALGORITHM_LIST_H