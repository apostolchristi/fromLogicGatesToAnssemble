//
// Created by Toor on 2/2/2022.
//

/*
 * add sub neg eq get lt and or not
 */

#ifndef VM_TRANSLATOR_ARITHMETIC_LOGICAL_COMMANDS_H
#define VM_TRANSLATOR_ARITHMETIC_LOGICAL_COMMANDS_H


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../HellpeingFunctions.h"

char *arithmetic_segments(char *command);



/* Integer addition: x+y */
void add();

/* Integer subtraction: x-y */
void sub();

/* Arithmetic negation: -y */
void neg();

/* Equality: true if x = y, else false */
void eq();

/* Greater than: true if x > y, else false */
void gt();

/* Less than: true if x < y, else false */
void lt();

/* Bit-wise: x And y */
void and();

/* Bit-wise: x Or y */
void or();

/* Bit-wise: Not y */
void not();

#endif //VM_TRANSLATOR_ARITHMETIC_LOGICAL_COMMANDS_H
