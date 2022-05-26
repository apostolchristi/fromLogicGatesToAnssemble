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

void bootstrap();


char *function_commands(char *command_type, char *arg1, char *arg2);

/* Write assembly code that effects the "call" command*/
void writeCall(char *functionName, char *nArgs);

/* Write assembly code that effects the "function" command*/
void writeFunction(char *functionName, char *nArgs);

/* Write assembly code that effects the "return" command*/
void writeReturn(char *functionName);

#endif //VM_TRANSLATOR_FUNCTION_COMMANDS_H
