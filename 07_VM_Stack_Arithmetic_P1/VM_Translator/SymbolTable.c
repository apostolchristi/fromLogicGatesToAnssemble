//
// Created by Toor on 1/20/2022.
//

#include "SymbolTable.h"
#define HT_SIZE_OF_50 50

static HashTable *assembler_mnemonics_hTable;

void constructor_SymbolTable() {

    if (assembler_mnemonics_hTable == NULL)
        assembler_mnemonics_hTable = initialize_preDefined_symbolsInstructions();
}

//TODO| Kill me please
void destructor_SymbolTable() {

    if(assembler_mnemonics_hTable != NULL) {
        ht_free(assembler_mnemonics_hTable);
        assembler_mnemonics_hTable = NULL;
    }
}

//TODO| Rename this function name
void substitute(char **symbol) {

    constructor_SymbolTable();

    HashTableItem *symbol_item = ht_search(assembler_mnemonics_hTable, *symbol);
    if (symbol_item != NULL) {
        *symbol = symbol_item->value;
    }
}



/* Represents special memory locations */
HashTable *initialize_preDefined_symbolsInstructions() {
    HashTable *ht = ht_create(HT_SIZE_OF_50);

    ht_insert(ht, "local", (void *) "LCL");
    ht_insert(ht, "argument", (void *) "ARG");
    ht_insert(ht, "this", (void *) "THIS");
    ht_insert(ht, "that", (void *) "THAT");
    ht_insert(ht, "temp", (void *) "5");

    return ht;

}