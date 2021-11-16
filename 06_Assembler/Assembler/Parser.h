//
// Created by Toor on 9/15/2021.
//

/* The Parser Module
 The main function of the parser is to break each assembly command into its under-lying
 components (fields and symbols).
 */
#ifndef ASSEMBLER_PARSER_H
#define ASSEMBLER_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HellperMethods.h"
#include "SymbolTable.h"
#include "HashTable/HashTable.h"


#define BITS_16 16 /* max array length */

char *hasMoreCommands(char *lineFromFile, size_t const *arrLength);

int reshape_the_string(const char *fileInput, char *instruction);

void string_copy(char *to, char *from);

char *commandType(char *instruction, size_t *length);

void handling_A_instruction(char *a_instruction, size_t *length, short *binary_instruction);

void handling_C_instruction(char *c_instruction, size_t *length, short *binary_instruction);

#endif //ASSEMBLER_PARSER_H
