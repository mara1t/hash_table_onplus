#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include "list_for_str//list.h"

const int max_str_len = 20;
const int base_table_size = 10;

class HashTable {
    
    int size;

    public:
        List *arr;
        unsigned find_hash (char *);
        int make_hash_table (FILE *);
        void print_hash_table ();
        HashTable ();
        ~HashTable ();
};