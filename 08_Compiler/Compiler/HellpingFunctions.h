//
// Created by Toor on 9/22/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>




#ifndef ASSEMBLER_HELPPERMETHODS_H
#define ASSEMBLER_HELPPERMETHODS_H

bool isDigit(char const *value);



int string_to_decimal(const char *string);
char *decimal_to_string(int *decimal);
short *decimal_to_16bitsBinary(int const *decimal_num);
char *_16bitsBinary_to_string(short * binary_value);

bool get_basename_of_theFile(char const *fileInput, char *instruction);




#endif //ASSEMBLER_HELPPERMETHODS_H
