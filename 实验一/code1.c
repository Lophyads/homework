#include <stdlib.h>
#include <stdio.h>
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
Node* Split(Node* head, int grep) {
    for (int i = 1; head != NULL && i < grep; i++) head = head->next;
    if (head == NULL) return NULL;
    Node* tmp = head->next;
    head->next = NULL;
    return tmp;
}
Node* merge(Node* left, Node* right, Node* PreTail) {
    Node* cur = PreTail;
    while (left != NULL && right != NULL) {
        if (left->index < right->index) {
            cur->next = left;
            cur = cur->next;
            left = left->next;
        }
        else {
            cur->next = right;
            cur = cur->next;
            right = right->next;
        }
    }
    cur->next = left != NULL ? left : right;
    while (cur->next != NULL) cur = cur->next;
    return cur;
}
void sort(List* ListNode) {
    Node* tmp = ListNode->head->next;
    int len = 0;
    while (tmp != NULL) {
        tmp = tmp->next;
        len++;
    }
    for (int grep = 1; grep < len; grep *= 2) {
        Node* cur = ListNode->head->next;
        Node* tail = ListNode->head;
        while (cur != NULL) {
            Node* left = cur;
            Node* right = Split(left, grep);
            cur = Split(right, grep);
            tail = merge(left, right, tail);
        }
    }
}
List* add(Node* node1, Node* node2) {
    List* Head = (List*)calloc(1, sizeof(List));
    Head->head = (Node*)calloc(1, sizeof(Node));
    Node* tail = Head->head;
    while (node1 != NULL && node2 != NULL) {
        if (node1->index < node2->index) {
            tail->next = node1;
            tail = tail->next;
            node1 = node1->next;
        }
        else if (node2->index < node1->index) {
            tail->next = node2;
            tail = tail->next;
            node2 = node2->next;
        }
        else {
            Node* node = (Node*)malloc(sizeof(Node));
            node->index = node1->index;
            node->coefficient = node1->coefficient + node2->coefficient;
            node->next = NULL;
            tail->next = node;
            tail = tail->next;
            node1 = node1->next;
            node2 = node2->next;
        }
    }
    tail->next = node1 != NULL ? node1 : node2;
    return Head;
}
List* Subtraction(Node* node1, Node* node2) {
    List* Head = (List*)calloc(1, sizeof(List));
    Head->head = (Node*)calloc(1, sizeof(Node));
    Node* tail = Head->head;
    while (node1 != NULL && node2 != NULL) {
        if (node1->index < node2->index) {
            tail->next = node1;
            tail = tail->next;
            node1 = node1->next;
        }
        else if (node2->index < node1->index) {
            tail->next = node2;
            tail = tail->next;
            node2 = node2->next;
        }
        else {
            Node* node = (Node*)malloc(sizeof(Node));
            node->index = node1->index;
            node->coefficient = node1->coefficient - node2->coefficient;
            node->next = NULL;
            tail->next = node;
            tail = tail->next;
            node1 = node1->next;
            node2 = node2->next;
        }
    }
    tail->next = node1 != NULL ? node1 : node2;
    return Head;
}
int main() {
    printf("请依次第一条多项式的指数和系数，系数为0时结束！\n");
    List* list1 = (List*)malloc(sizeof(List));
    list1->head = (Node*)calloc(1, sizeof(Node));
    list1->tail = list1->head;
    while (1) {
        int coefficient, index;
        printf("请输入系数:");
        scanf("%d", &coefficient);
        if (coefficient == 0) break;
        printf("请输入指数:");
        scanf("%d", &index);
        insert(list1, coefficient, index);
    }
    printf("请依次第二条多项式的指数和系数，系数为0时结束！\n");
    List* list2 = (List*)malloc(sizeof(List));
    list2->head = (Node*)calloc(1, sizeof(Node));
    list2->tail = list2->head;
    while (1) {
        int coefficient, index;
        printf("请输入系数:");
        scanf("%d", &coefficient);
        if (coefficient == 0) break;
        printf("请输入指数:");
        scanf("%d", &index);
        insert(list2, coefficient, index);
    }
    sort(list1);
    sort(list2);
    printf("p(x) = ");
    printList(list1);
    printf("q(x) = ");
    printList(list2);
    List* list3 = add(list1->head, list2->head);
    List* list4 = Subtraction(list1->head,list2->head);
    printList(list3);
    printList(list4);
}