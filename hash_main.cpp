#include <stdio.h>
#include "hash.h"

void print_hello (HashTable MyHashTable) {
    printf("hello\n");
}

int main() {

    int size = FileSize();

    HashTable MyTable(size);

    MyTable.MakeTable();

    MyTable.Print();


    //print_hello (MyTable);

    return 0;
}