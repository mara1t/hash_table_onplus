#include "hash.h"

int FileSize () 
{
    FILE *file_onegin = fopen("og.txt", "r");
    assert(file_onegin != NULL);

    char *tmp_str = new char [20];
    int size = 0;


    while (fscanf(file_onegin, "%s", tmp_str) != EOF) {
        size++;
    }

    delete[] tmp_str;
    
    fclose(file_onegin);
    return size;

}

HashTable::HashTable () 
{
    size = base_table_size;

    arr = new List [size];

    for (int i = 0; i < size; i++) 
        ListCtor(&(arr[i]));
        
    printf("this default ctor\n");
}
HashTable::HashTable (int size_) 
{
    
    size = size_;

    arr = new List [size];

    for (int i = 0; i < size; i++) { 
        ListCtor(&(arr[i]));\
    }
        
    printf("this size ctor\n");
}

HashTable::~HashTable () 
{
    size = 0;
    
    delete[] arr; 

    printf("this default dtor\n");

}

void HashTable::Print () 
{
    FILE *output_file = fopen("output.txt", "w");

    
    for (int i = 0; i < size; i++) {
        fprintf(output_file, "[%d] = ", i);
        PrintList(&(arr[i]), output_file);
    }
    

    fclose(output_file);
}

int HashTable::FindElem (char *value) 
{
    unsigned tmp_hash = FindHash(value);
    int tmp_pos = (arr[tmp_hash]).next[0];

    while (tmp_pos != 0) {

        if (strcmp(value, (arr[tmp_hash]).mass[tmp_pos]) == 0) {
            return tmp_pos;
        }

        tmp_pos = (arr[tmp_hash]).next[tmp_pos];
    }

        
    if (tmp_pos == 0) {
        printf("No elem\n");
        return -1;
    }
    
    return tmp_pos;
}

unsigned HashTable::FindHash (char *str)
{
    
    unsigned hash = 0;
    char one_symb = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        hash += pow(2, i) * (str[i] - 127);
        i++;
    }

    hash = hash % size;


    return hash;
}

int HashTable::MakeTable ()
{

    FILE *file_onegin = fopen("og.txt", "r");

    char *cur_str = (char*) calloc (max_str_len, sizeof(char));

    while (fscanf(file_onegin, "%s ", cur_str) != EOF) {  

        int tmp_hash = FindHash(cur_str);
        
        int tmp_pos = (arr[tmp_hash]).next[0];

        while (tmp_pos != 0) {

           
            if (strcmp(cur_str, (arr[tmp_hash]).mass[tmp_pos]) == 0) {

                (arr[tmp_hash]).amount[tmp_pos]++;                
                break;
            }
        
            tmp_pos = (arr[tmp_hash]).next[tmp_pos];
        }

        if (tmp_pos == 0) {
            ListTailAdd(&(arr[tmp_hash]), cur_str);
            (arr[tmp_hash]).amount[(arr[tmp_hash]).previous[0]]++; //instead of 0 - tmp_pos
        }
        
    }
    free(cur_str);
    fclose(file_onegin);

    return 0;
}

int HashTable::GraphPrint () 
{

    FILE *graph = fopen("graph.txt", "w");

    int global_counter = 0;
    int print_counter = 0;

    fprintf(graph, "digraph G{\n"
                   "\trankdir=LR;\n");
    
    int lst_counter = 0;

    while (lst_counter < size) {

        if ((arr[lst_counter]).size == 0) {
            lst_counter++;
            continue;
        }

        int position = (arr[lst_counter]).next[0];
        int for_one_lst_counter = 0;
        int print_counter = 0;

        while ((arr[lst_counter]).next[position] != 0) {
            fprintf(graph, "\tstruct%d [shape=record,label=\"  \\n%s | <f0> amount\\n %d\" ];\n", global_counter, (arr[lst_counter]).mass[position], (arr[lst_counter]).amount[position]);
            for_one_lst_counter++;
            global_counter++;
            position = (arr[lst_counter]).next[position];
        }

        fprintf(graph, "\tstruct%d [shape=record,label=\"  \\n%s | <f0> amount\\n %d\" ];\n", global_counter, (arr[lst_counter]).mass[position], (arr[lst_counter]).amount[position]);
        global_counter++;

        lst_counter++;
    }

    fprintf(graph, "\t");
        

    while (global_counter > 0) {
        fprintf(graph, "struct%d:<f0>", print_counter);
        if (global_counter != 1)
            fprintf(graph, " -> ");

        print_counter++;
        global_counter--;
    }

    fprintf(graph, ";\n");


    fprintf(graph, "}");


    fclose(graph);

    return 0;
}