//
// Created by Toor on 9/22/2021.
//

#include <stdio.h>
#include <stdlib.h>



#ifndef ASSEMBLER_HELPPERMETHODS_H
#define ASSEMBLER_HELPPERMETHODS_H

short string_to_decimal(const char *string,  size_t const *length);
char *_16bitsBinary_to_string(short *binary_value);
void string_copy(char *to, char *from);
void decimal_to_16bitsBinary(const short *decimal_num, short *const binary_instruction);

#endif //ASSEMBLER_HELPPERMETHODS_H
