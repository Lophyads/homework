#include "code2.h"
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
    List* list3 = add(list1->head->next, list2->head->next);
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