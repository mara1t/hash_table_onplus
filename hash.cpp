#include "hash.h"

HashTable::HashTable () 
{
    this->size = base_table_size;

    this->arr = (List*) calloc (this->size, sizeof(List));

    for (int i = 0; i < this->size; i++) 
        ListCtor(&(this->arr[i]));
}

HashTable::~HashTable () 
{
    this->size = 0;
    for (int i = 0; i < this->size; i++) 
        ListDtor(&(this->arr[i]));

}

void HashTable::print_hash_table () 
{
    printf("START TABLE-------------------\n");
    for (unsigned i = 0; i < this->size; i++) {
        printf("[%d] = ", i);
        PrintList(&(this->arr[i]));
    }
    printf("END TABLE---------------------\n");
}

unsigned HashTable::find_hash (char *str)
{
    
    unsigned hash = 0;
    char one_symb = 0;
    int i = 0;
    
    while (str[i] != '\0') {
        hash += pow(2, i) * (str[i] - 127);
        i++;
    }

    hash = hash % this->size;

    return hash;
}

int HashTable::make_hash_table (FILE *onegin)
{
    char *cur_str = (char*) calloc (max_str_len, sizeof(char));

    while (fscanf(onegin, "%s ", cur_str) != EOF) {  

        unsigned tmp_hash = find_hash(cur_str);
        int tmp_pos = (this->arr[tmp_hash]).next[0];
    
        while (tmp_pos != 0) {

            if (strcmp(cur_str, (this->arr[tmp_hash]).mass[tmp_pos]) == 0) {
                
                (this->arr[tmp_hash]).amount[tmp_pos]++;
                break;
            }
        
            tmp_pos = (this->arr[tmp_hash]).next[tmp_pos];
        }

        if (tmp_pos == 0) {
            ListTailAdd(&(this->arr[tmp_hash]), cur_str);
            (this->arr[tmp_hash]).amount[(this->arr[tmp_hash]).previous[tmp_pos]]++;
        }
        
    }

    free(cur_str);

    return 0;
}