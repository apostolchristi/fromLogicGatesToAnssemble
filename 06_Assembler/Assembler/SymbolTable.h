//
// Created by Toor on 9/15/2021.
//


#ifndef ASSEMBLER_SYMBOLTABLE_H
#define ASSEMBLER_SYMBOLTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "HashTable/HashTable.h"
#include "HellpeingFunctions.h"


void constructor_SymbolTable();
void destructor_SymbolTable();
void addEntry(char *symbol, short address, short *binary_instruction);
bool contains(char *symbol, short *binary_instruction);
short getAddress(char *symbol);
HashTable *initialize_jump_instructions();
HashTable *initialize_dest_instructions();
HashTable *initialize_comp_instructions();
HashTable *initialize_preDefined_symbolsInstructions();

#endif //ASSEMBLER_SYMBOLTABLE_H
