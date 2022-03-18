#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <assert.h>
#include "list_for_str//list.h"

const int max_str_len = 20;
const int base_table_size = 10;

class HashTable {
    
    int size;

    public:
        List *arr;
        unsigned FindHash (char *);
        int MakeTable ();
        void Print ();
        int FindElem (char *value);
        int GraphPrint();
        HashTable ();
        HashTable (int);
        ~HashTable ();
};

int FileSize ();
