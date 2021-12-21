//
// Created by Toor on 11/25/2021.
//

/**
 * Code module translates Hack assembly language mnemonics into binary codes.
 */


#ifndef UNTITLED_CODE_H
#define UNTITLED_CODE_H

#include <stdio.h>
#include <stdlib.h>
#include "HashTable/HashTable.h"
#include "Parser.h"


#define COMP_ARRAY_LENGTH 6
#define DESTJUMP_ARRAY_LENGTH 3

typedef struct comp_bits comp_bits;
typedef struct destjump_bits destjump_bits;

struct comp_bits {
    short instructions[COMP_ARRAY_LENGTH];
    short a;
};

struct destjump_bits {
    short instructions[DESTJUMP_ARRAY_LENGTH];
};

void destructor_Code();
HashTable *initialize_jump_instructions();
HashTable *initialize_dest_instructions();
HashTable *initialize_comp_instructions();
void jmp_instructions(short *binary_instruction, char *key);
void dest_instructions(short *binary_instruction, char *key);
void comp_instructions(short *binary_instruction, char *key);




#endif //UNTITLED_CODE_H
