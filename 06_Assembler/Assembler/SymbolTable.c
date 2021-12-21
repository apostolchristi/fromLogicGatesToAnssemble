
//
// Created by Toor on 9/30/2021.
//

#include "SymbolTable.h"

#define A_POSITION 3
#define COMP_POSITION 4
#define DEST_POSITION 10
#define JMP_POSITION 13
#define HT_SIZE_OF_10 10
#define HT_SIZE_OF_30 30
#define HT_SIZE_OF_50 50
#define BITS_16 16
#define HT_SIZE_OF_500 500

static HashTable *symbols_hTable;

void constructor_SymbolTable() {

    // Create label_symbols table
    if (symbols_hTable == NULL)
        symbols_hTable = initialize_preDefined_symbolsInstructions();
}

void destructor_SymbolTable() {

    if(symbols_hTable != NULL) {
        ht_free(symbols_hTable);
        symbols_hTable = NULL;
    }
}

void addEntry(char *symbol, short address, short *binary_instruction) {

    constructor_SymbolTable();
    bool flag = contains(symbol, binary_instruction);

    if (flag == false) {
        printf("%d\n", address);
        ht_insert(symbols_hTable, symbol, address);
    }

}

bool contains(char *symbol, short *binary_instruction) {

    HashTableItem *symbol_item = ht_search(symbols_hTable, symbol);

    //If true, the decimal value is put into the binary_instruction array
    if (symbol_item != NULL) {
        short decimal_value = getAddress(symbol);
            decimal_to_16bitsBinary(&decimal_value, binary_instruction);

        return true;
    }

    return false;
}

short getAddress(char *symbol) {

    HashTableItem *symbol_item = ht_search(symbols_hTable, symbol);
    return (short) symbol_item->value;
}


/* Represents special memory locations */
HashTable *initialize_preDefined_symbolsInstructions() {
    HashTable *ht = ht_create(HT_SIZE_OF_50);

    ht_insert(ht, "R0", (void *) 0);
    ht_insert(ht, "R1", (void *) 1);
    ht_insert(ht, "R2", (void *) 2);
    ht_insert(ht, "R3", (void *) 3);
    ht_insert(ht, "R4", (void *) 4);
    ht_insert(ht, "R5", (void *) 5);
    ht_insert(ht, "R6", (void *) 6);
    ht_insert(ht, "R7", (void *) 7);
    ht_insert(ht, "R8", (void *) 8);
    ht_insert(ht, "R9", (void *) 9);
    ht_insert(ht, "R10", (void *) 10);
    ht_insert(ht, "R11", (void *) 11);
    ht_insert(ht, "R12", (void *) 12);
    ht_insert(ht, "R13", (void *) 13);
    ht_insert(ht, "R14", (void *) 14);
    ht_insert(ht, "R15", (void *) 15);
    ht_insert(ht, "SCREEN", (void *) 16384);
    ht_insert(ht, "KBD", (void *) 24576);

    ht_insert(ht, "SP", (void *) 0);
    ht_insert(ht, "LCL", (void *) 1);
    ht_insert(ht, "ARG", (void *) 2);
    ht_insert(ht, "THIS", (void *) 3);
    ht_insert(ht, "THAT", (void *) 4);


    return ht;

}
