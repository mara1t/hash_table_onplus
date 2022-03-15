#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef char elem_t;

#define $$$ printf("line=%d\n", __LINE__);

typedef struct list {

    char **mass;
    int *amount;
    int *next;
    int *previous;
    int capacity;
    int free_first_pos;
    int size;
    int sorted;
} List;

const int BASE_LIST_SIZE = 100;


int ListCtor        (List *lst);
int ListDtor        (List* lst);
int ListDelete      (List* lst, const int number);
int ListInsertAft   (List* lst, const int number, char *value);
int PrintList       (List *lst, FILE * output);
int graph_print     (List  lst);
int ListHeadAdd     (List *lst, char *value);
int ListTailAdd     (List *lst, char *value);
int ListInsertBef   (List *lst, const int number, char *value);
int Sort            (List *lst);
int ListInsertAftLogic (List *lst, const int number, char *value);
int ListRealloc     (List *lst, const int plus_capacity);