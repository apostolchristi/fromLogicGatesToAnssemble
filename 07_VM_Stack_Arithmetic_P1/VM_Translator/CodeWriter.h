//
// Created by Toor on 1/12/2022.
//

#ifndef VM_TRANSLATOR_CODEWRITER_H
#define VM_TRANSLATOR_CODEWRITER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "HellpeingFunctions.h"
#include "VM_Languange/Memory_Access_Comands.h"
#include "VM_Languange/Arithmetic_Logical_Commands.h"
#include "VM_Languange/Branching_Commands.h"
#include "VM_Languange/Function_Commands.h"


/* Informs the code writer that the translation of a new VM file is started. */
void setFileName(char *fileName);
char *writeInit();

char *writeDelegator(char *command_type, char *arg1, char *arg2, char const *file_name);

/* Writes assembly code that is the translation of the given commands, where command is either C_PUSH or C_POP. */
char *writePushPop(char *command_type, char *arg1, char *arg2, char const *file_name);

/* Writes assembly code that is the translation of the given arithmetic commands.*/
char *writeArithmetic(char *command);

/* Writes assembly code that effects the "label" or "goto" or "if-goto commands*/
char *writeBranching(char *arg1, char *arg2);

/* Writes assembly code that effects the "call", "return" and "function" commands */
char *writeFunctions(char *command_type, char *arg1, char *arg2);







#endif //VM_TRANSLATOR_CODEWRITER_H
