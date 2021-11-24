//
// Created by Toor on 9/15/2021.
//


#ifndef ASSEMBLER_SYMBOLTABLE_H
#define ASSEMBLER_SYMBOLTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "HashTable/HashTable.h"
#include "Parser.h"

#define COMP_ARRAY_LENGTH 6
#define DESTJUMP_ARRAY_LENGTH 3

typedef struct comp_bits comp_bits;
typedef struct destjump_bits destjump_bits;
;
struct comp_bits {
    short comp[COMP_ARRAY_LENGTH];
    short a;
    short arrayLength;
};

struct destjump_bits {
    short destjump[DESTJUMP_ARRAY_LENGTH];
    short arrayLength;
};


HashTable *jump_instructions();
HashTable *dest_instructions();
HashTable *comp_instructions();
HashTable *variable_symbols();
HashTable *label_symbols();
HashTable *pre_defined_symbols();
void jmp_parse(HashTableItem *item, short *binary_instruction);
void dest_parse(HashTableItem *item, short *binary_instruction);
void comp_parse(HashTableItem *item, short *binary_instruction);

#endif //ASSEMBLER_SYMBOLTABLE_H
