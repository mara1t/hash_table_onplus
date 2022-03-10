#include <stdio.h>
#include <stdlib.h>

typedef char elem_t;

typedef struct list {

    elem_t **mass;
    int *amount;
    int *next;
    int *previous;
    int capacity;
    int free_first_pos;
    int size;
    int sorted;
} List;

const int BASE_LIST_SIZE = 100;

///===============================================

#define $$$ printf("here on line=%d\n", __LINE__);

/*
#define PR printf("\nmass\n");\
    for (int i = 0; i < lst.capacity; i++)\
    {\
        printf("%d=%d ", i, lst.mass[i]);\
    }\
    printf("\nnext\n");\
    for (int i = 0; i < lst.capacity; i++)\
    {\
        printf("%d=%d ", i, lst.next[i]);\
    }\
    printf("\nprev\n");\
    for (int i = 0; i < lst.capacity; i++)\
    {\
        printf("%d=%d ", i, lst.previous[i]);\
    }\
*/
///===========================================================

#define INSERT_AFT(num, val)    ListInsertAft(&lst, num, val)
#define INSERT_BEF(num, val)    ListInsertBef(&lst, num, val)
#define DELETE(num)             ListDelete(&lst, num)
#define TAILADD(num)            ListTailAdd(&lst, num)
#define HEADADD(num)            ListHeadAdd(&lst, num)
#define PRINTLIST               PrintList(&lst)
#define GRAPHPRINT              graph_print(lst)

int ListCtor        (List *lst);
int ListDtor        (List* lst);
int ListDelete      (List* lst, const int number);
int ListInsertAft   (List* lst, const int number, elem_t *value);
int PrintList       (List *lst);
int graph_print     (List  lst);
int ListHeadAdd     (List *lst, elem_t *value);
int ListTailAdd     (List *lst, elem_t *value);
int ListInsertBef   (List *lst, const int number, elem_t *value);
int Sort            (List *lst);
int ListInsertAftLogic (List *lst, const int number, elem_t *value);
int ListRealloc     (List *lst, const int plus_capacity);