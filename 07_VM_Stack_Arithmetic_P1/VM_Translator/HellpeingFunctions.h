//
// Created by Toor on 9/22/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>




#ifndef ASSEMBLER_HELPPERMETHODS_H
#define ASSEMBLER_HELPPERMETHODS_H

bool isDigit(char const *command);
int string_to_decimal(const char *string);
char *decimal_to_string(int *decimal);
short *decimal_to_16bitsBinary(int const *decimal_num);
char *_16bitsBinary_to_string(short * binary_value);

bool get_basename_of_theFile(char const *fileInput, char *instruction);

char *bootstrap_code();
void initializer_dir(char const *input_file_dest, char const *output_file_dest);

#endif //ASSEMBLER_HELPPERMETHODS_H
