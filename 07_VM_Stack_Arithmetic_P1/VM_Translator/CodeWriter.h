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


/* Informs the code writer that the translation of a new VM file is started. */
void setFileName(char *fileName);

/* Writes the assembly code that is the translation of the given arithmetic command.*/
char *writeArithmetic(char *command);

/* Writes the assembly code that is the transaltion of the given command, where command is either C_PUSH or C_POP. */
char *writePushPop(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name);






#endif //VM_TRANSLATOR_CODEWRITER_H
