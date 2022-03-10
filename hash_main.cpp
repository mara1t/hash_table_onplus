#include <stdio.h>
#include "hash.h"

void print_hello (HashTable MyHashTable) {
    printf("hello\n");
}

int main() {

    FILE *onegin = fopen ("onegin.txt", "r");

    HashTable MyHashTable;

    MyHashTable.make_hash_table(onegin);

    MyHashTable.print_hash_table();

    //print_hello (MyHashTable);

    fclose(onegin);

    return 0;
}