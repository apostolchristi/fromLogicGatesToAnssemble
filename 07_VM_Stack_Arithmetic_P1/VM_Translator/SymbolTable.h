//
// Created by Toor on 1/20/2022.
//

#ifndef VM_TRANSLATOR_SYMBOLTABLE_H
#define VM_TRANSLATOR_SYMBOLTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "HashTable/HashTable.h"

void constructor_SymbolTable();
void destructor_SymbolTable();
void substitute(char **symbol);


HashTable *initialize_preDefined_symbolsInstructions();

#endif //VM_TRANSLATOR_SYMBOLTABLE_H
