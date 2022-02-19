//
// Created by Toor on 2/2/2022.
//

/*
 * label label
 * goto label
 * if-goto label
 * */


#ifndef VM_TRANSLATOR_BRANCHING_COMMANDS_H
#define VM_TRANSLATOR_BRANCHING_COMMANDS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../HellpeingFunctions.h"

char *branching_commands(char *command, char *command_value);


/* Writes assembly code that effects the "label" command*/
void writeLabel(char *command_value);

/* Writes assembly code that effects the "goto" command*/
void writeGoto(char *command_value);

/* Writes assembly code that effects the "if-goto" command*/
void writeIf(char *command_value);

#endif //VM_TRANSLATOR_BRANCHING_COMMANDS_H
