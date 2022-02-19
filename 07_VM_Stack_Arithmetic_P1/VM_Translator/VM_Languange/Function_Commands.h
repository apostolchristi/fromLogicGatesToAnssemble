//
// Created by Toor on 2/2/2022.
//

/* function functionName nVars
 * call functionName nArgs
 * return
 */

#ifndef VM_TRANSLATOR_FUNCTION_COMMANDS_H
#define VM_TRANSLATOR_FUNCTION_COMMANDS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../HellpeingFunctions.h"

char *function_commands(char *command, char *command_value);

/* Write assembly code that effects the "call" command*/
void writeCall(char *functionName, int numArgs);

/* Write assembly code that effects the "return" command*/
void writeReturn(void);

/* Write assembly code that effects the "function" command*/
void writeFunction(char *functionName, int numLocals);

#endif //VM_TRANSLATOR_FUNCTION_COMMANDS_H
