#ifndef ALGORITHM_CODE2_H
#define ALGORITHM_CODE2_H
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
Node* Split(Node* head, int grep) {//分割
    for (int i = 1; head != NULL && i < grep; i++) head = head->next;
    if (head == NULL) return NULL;
    Node* tmp = head->next;
    head->next = NULL;
    return tmp;
}
Node* merge(Node* left, Node* right, Node* PreTail) {//合并
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
void sort(List* ListNode) {//排序
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
List* add(Node* node1, Node* node2) {//相加
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
List* Subtraction(Node* node1, Node* node2) {//相减
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
    while(tmp != NULL){
        Node* t = tmp;
        tmp = tmp->next;
        free(t);
    }
    free(list);
}
#endif //ALGORITHM_CODE2_H