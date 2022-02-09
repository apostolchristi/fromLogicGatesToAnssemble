//
// Created by Toor on 2/2/2022.
//

/*
 * pop segment i
 * push segment i
 */

#ifndef VM_TRANSLATOR_MEMORY_ACCESS_COMANDS_H
#define VM_TRANSLATOR_MEMORY_ACCESS_COMANDS_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../SymbolTable.h"
#include "../HellpeingFunctions.h"

char *push_memory_access_segments(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name);
char *pop_memory_access_segments(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name);
void init_assembly_string(char *mnemonic_arg1, char *mnemonic_arg2);

/* Pseudo-segment that holds all the constants in the range 0 ... 32767*/
void push_constant_segment(void);

/* A two-entry segment that gold the base address of the THIS and THAT segments*/
void push_pointer_segment(char *mnemonic_arg2);
void pop_pointer_segment(char *mnemonic_arg2);

/* Stores static variables shared by all functions in the same .vm file.*/
void push_static_segment(char *file_name, char *mnemonic_arg2);
void pop_static_segment(char *file_name, char *mnemonic_arg2);

/* Fixed eight-entry segment that gold temporary variables for general use*/
void push_temp_segment(void);
void pop_temp_segment(void);

/* Segment_pointers: LCL, ARG, THIS, THAT
 * LCL (local): Stores the function's local variables.
 * ARG (argument): Stores the function's arguments.
 * THIS (this) and THAT (that): General-purpose segments. Can be made to correspond
 to different areas in the heap. Any VM function can use these segments to manipulate selected areas on the heap.
 */
void push_segment_pointers(char *segment_type);
void pop_segment_pointers(char *segment_type);


#endif //VM_TRANSLATOR_MEMORY_ACCESS_COMANDS_H
