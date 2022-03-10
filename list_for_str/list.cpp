#include "list.h"

int ListCtor (List *lst) {

    if (lst == NULL) {
        printf("err in ctor\n");
        return -1;
    }

    lst->mass = (elem_t**) calloc (BASE_LIST_SIZE, sizeof(elem_t*));
    lst->next = (int*) calloc (BASE_LIST_SIZE, sizeof(int));
    lst->previous = (int*) calloc (BASE_LIST_SIZE, sizeof(int));
    lst->amount = (int*) calloc (BASE_LIST_SIZE, sizeof(int));


    lst->free_first_pos = 1;
    lst->size = lst->next[0] = lst->previous[0] = lst->sorted = 0;
    lst->capacity = BASE_LIST_SIZE;

    for (int i = 1; i < BASE_LIST_SIZE - 1; i++)
        lst->next[i] = - ((i + 1) % BASE_LIST_SIZE);
    
    for (int i = 2; i < BASE_LIST_SIZE; i++)
        lst->previous[i] = - ((i - 1) % BASE_LIST_SIZE);

    return 0;
}

int ListDtor (List* lst) {

    if (lst == NULL)
    {
        printf("Err in dtor\n");
        return -1;
    }
    lst->size = lst->next[0] = lst->previous[0] = lst->free_first_pos = lst->sorted = 0;
    
    free(lst->mass);
    free(lst->next);
    free(lst->previous);    

    return 0;
}

int ListRealloc (List *lst, const int plus_capacity) {
    /*if (lst->size < lst->capacity) {
        printf("err in realoc\n");
        return -1;
    }*/

    lst->mass = (elem_t**) realloc (lst->mass, (plus_capacity + lst->capacity) * sizeof(elem_t*));
    lst->next = (int*) realloc (lst->next, (plus_capacity + lst->capacity) * sizeof(int));
    lst->previous = (int*) realloc (lst->previous, (plus_capacity + lst->capacity) * sizeof(int));

    for (int i = lst->capacity; i < lst->capacity + plus_capacity; i++) {
        lst->next[i] = - ((i + 1) % (lst->capacity + plus_capacity));
    }
    lst->next[lst->capacity + plus_capacity - 1] = - lst->free_first_pos;

    for (int i =  lst->capacity; i < lst->capacity + plus_capacity; i++) {
        lst->previous[i] = - ((i - 1) % (lst->capacity + plus_capacity));
    }
    lst->free_first_pos = lst->capacity;

    lst->capacity = lst->capacity + plus_capacity;

    return 0;
}

int ListDelete (List* lst, const int number) {
    
    if (lst->size == 0) {
        printf("ERROR in delite\n");
        return -1;
    }

    if (number == lst->next[0])
        lst->next[0] = lst->next[lst->next[0]];

    if (number == lst->previous[0])
        lst->previous[0] = lst->next[lst->previous[0]];


    lst->next[lst->previous[number]] = lst->next[number];
    lst->previous[lst->next[number]] = lst->previous[number];
    lst->next[number] = lst->free_first_pos;
    lst->previous[number] = 0;
    lst->previous[lst->free_first_pos] = number;
    
    lst->free_first_pos = number;
    lst->size--;

    return 0;
}

int ListInsertAft (List *lst, const int number, elem_t *value) {

    if (number == lst->previous[0])
        lst->previous[0] = lst->free_first_pos;

    if (lst->capacity == lst->size - 1) {
        ListRealloc (lst, 20);
    }

    int tmp_pos = - lst->next[lst->free_first_pos];
    lst->mass[lst->free_first_pos] = value;
    lst->next[lst->free_first_pos] = lst->next[number];
    lst->previous[lst->free_first_pos] = number;
    lst->previous[lst->next[number]] = lst->free_first_pos;
    lst->next[number] = lst->free_first_pos;
    lst->free_first_pos = tmp_pos;

    lst->size++;

    return 0;
}

int ListInsertBef (List *lst, const int number, elem_t *value) {

    if (number == lst->next[0])
        lst->next[0] = lst->free_first_pos;

    if (lst->capacity == lst->size - 1) {
        ListRealloc (lst, 20);
    }

    int tmp_pos = - lst->next[lst->free_first_pos];

    lst->mass[lst->free_first_pos] = value;
    lst->next[lst->free_first_pos] = number;
    lst->previous[lst->free_first_pos] = lst->previous[number];
    lst->previous[number] = lst->free_first_pos;
    lst->next[lst->previous[lst->free_first_pos]] = lst->free_first_pos;
    
    lst->free_first_pos = tmp_pos;

    lst->size++;

    return 0;
}

int ListInsertAftLogic (List *lst, const int number, elem_t *value) {

    if (number >= lst->size) {
        printf("Not enough size\n");
        return -1;
    }

    if (lst->capacity == lst->size - 1) {
        ListRealloc (lst, 20);
    }

    if (lst->sorted == 1) {
        ListInsertAft(lst, number + 1, value);
        
        return 0;
    }
    else {
        Sort (lst);
        
        ListInsertAft (lst, number + 1, value);
        
        return 0;
    }
}

int Sort (List *lst) {

    if (lst->size <= 1) {
        return 0;
    }

    elem_t **tmp_arr_mass = (elem_t**) calloc (lst->size + 1, sizeof(elem_t*));
    int *tmp_arr_next = (int*) calloc (lst->size + 1, sizeof(int));
    int *tmp_arr_prev = (int*) calloc (lst->size + 1, sizeof(int));

    int cur_pos = lst->next[0];

    tmp_arr_next[0] = 1;
    tmp_arr_prev[0] = lst->size;
    tmp_arr_mass[0] = 0;

    for (int i = 1; i <= lst->size; i++) {
        
        tmp_arr_mass[i] = lst->mass[cur_pos];
        
        tmp_arr_next[i] = i + 1;

        tmp_arr_prev[i] = i - 1;

        cur_pos = lst->next[cur_pos];

    }
    tmp_arr_next[lst->size] = 0;
    

    for (int i = 0; i <= lst->size; i++) {
        lst->mass[i] = tmp_arr_mass[i];
        lst->next[i] = tmp_arr_next[i];
        lst->previous[i] = tmp_arr_prev[i]; 
    }


    free(tmp_arr_mass);
    free(tmp_arr_next);
    free(tmp_arr_prev);

    return 0;
}


int ListHeadAdd (List *lst, elem_t *value) {

    if (lst->free_first_pos == 0) {
        printf("No place for adding\n");
        return -1;
    }

    if (lst->capacity == lst->size - 1) {
        ListRealloc (lst, 20);
    }
   
    lst->mass[lst->free_first_pos] = value;
    lst->next[lst->free_first_pos] = lst->next[0];
    lst->previous[lst->next[0]] = lst->free_first_pos;
    lst->next[0] = lst->free_first_pos;
    lst->previous[lst->free_first_pos] = 0;

    lst->free_first_pos = - lst->next[lst->free_first_pos];
    
    lst->size++;

    return 0;
}

int ListTailAdd (List *lst, elem_t *value) {

    if (lst->free_first_pos == 0) {
        printf("No place for adding\n");
        return -1;
    }

    if (lst->capacity == lst->size - 1) {
        ListRealloc (lst, 20);
    }
    
    lst->mass[lst->free_first_pos] = value;
    lst->next[lst->free_first_pos] = 0;
    lst->previous[lst->free_first_pos] = lst->previous[0];
    lst->next[lst->previous[0]] = lst->free_first_pos;
    lst->previous[0] = lst->free_first_pos;
    lst->free_first_pos = - lst->next[lst->free_first_pos];
    
    lst->size++;

    return 0;
}


int PrintList (List *lst) {

    if (lst->size == 0) {
        printf("0\n");
        return -1;
    }

    int position = lst->next[0];
    int counter = 0;

    while (lst->next[position] > 0 && counter++ < lst->size) {
        printf("%d ", lst->amount[position]);
        position = lst->next[position];
        
    }

    printf("%d\n", lst->amount[position]);

    return 0;
}
/*
int graph_print (const List lst) {

    FILE *graph = fopen("graph.txt", "w");

    int position = lst.next[0];
    int counter = 0;
    int print_counter = 0;

    if (lst.next[0] == 0) {
        printf("error in dump");
        return -1;
    }

    fprintf(graph, "digraph G{\n"
                   "\trankdir=LR;\n");
    
    while (lst.next[position] != 0) {
        fprintf(graph, "\tstruct%d [shape=record,label=\"  mass\\n%d | <f0> next\\n %d | previous\\n %d\" ];\n", counter, lst.mass[position], lst.next[position], lst.previous[position]);
        counter++;
        position = lst.next[position];
    }

    fprintf(graph, "\tstruct%d [shape=record,label=\"  mass\\n%d | <f0> next\\n %d | previous\\n %d\" ];\n", counter, lst.mass[position], lst.next[position], lst.previous[position]);
    fprintf(graph, "\t");
    
    while (counter >= 0) {
        fprintf(graph, "struct%d:<f0>", print_counter);
        if (counter != 0)
            fprintf(graph, " -> ");

        print_counter++;
        counter--;
    }

    fprintf(graph, ";\n");


    fprintf(graph, "}");


    fclose(graph);

    return 0;
}

*/