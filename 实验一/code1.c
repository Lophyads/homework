#include <stdlib.h>
#include <stdio.h>
#include "List.h"
Node* Split(Node* head, int grep) {
    for (int i = 1; head != NULL && i < grep; i++) head = head->next;//head走到分割点
    if (head == NULL) return NULL;
    Node* tmp = head->next;
    head->next = NULL;//把末尾与其他部分砍断
    return tmp;//返回分割后剩下部分链表的开头
}
Node* merge(Node* left, Node* right, Node* PreTail) {//归并
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
    while (tmp != NULL) {//获得链表长度
        tmp = tmp->next;
        len++;
    }
    for (int grep = 1; grep < len; grep *= 2) {
        Node* cur = ListNode->head->next;
        Node* tail = ListNode->head;
        while (cur != NULL) {
            Node* left = cur;//left指向第一段链表的开头
            Node* right = Split(left, grep);//从left位置开始分割grep长度,right指向第二段链表的开头
            cur = Split(right, grep);//从right位置开始分割grep长度
            tail = merge(left, right, tail);//将两段链表归并
        }
    }
}
List* add(Node* node1, Node* node2) {//加法
    List* Head = (List*)calloc(1, sizeof(List));
    Head->head = (Node*)calloc(1, sizeof(Node));
    Node* tail = Head->head;
    while (node1 != NULL && node2 != NULL) {
        if (node1->index < node2->index) {
            Node* tmp = (Node*)malloc(sizeof(Node));
            tmp->index = node1->index;
            tmp->coefficient = node1->coefficient;
            tail->next = tmp;
            tail = tail->next;
            node1 = node1->next;
        }
        else if (node2->index < node1->index) {
            Node* tmp = (Node*)malloc(sizeof(Node));
            tmp->index = node2->index;
            tmp->coefficient = node2->coefficient;
            tail->next = tmp;
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
List* Subtraction(Node* node1, Node* node2) {//减法
    List* Head = (List*)calloc(1, sizeof(List));
    Head->head = (Node*)calloc(1, sizeof(Node));
    Node* tail = Head->head;
    while (node1 != NULL && node2 != NULL) {
        if (node1->index < node2->index) {
            Node* tmp = (Node*)malloc(sizeof(Node));
            tmp->index = node1->index;
            tmp->coefficient = node1->coefficient;
            tail->next = tmp;
            tail = tail->next;
            node1 = node1->next;
        }
        else if (node2->index < node1->index) {
            Node* tmp = (Node*)malloc(sizeof(Node));
            tmp->index = node2->index;
            tmp->coefficient = node2->coefficient;
            tail->next = tmp;
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
    List* list3 = add(list1->head->next, list2->head->next);//创建链表是head为空节点,所以传入head->next;
    List* list4 = Subtraction(list1->head->next,list2->head->next);
    printf("p(x) + q(x) = ");
    printList(list3);
    printf("p(x) - q(x) = ");
    printList(list4);
    DeleteList(list1);
    DeleteList(list2);
    DeleteList(list3);
    DeleteList(list4);
}