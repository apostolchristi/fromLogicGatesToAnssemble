//
// Created by Toor on 9/22/2021.
//

#include "HellpeingFunctions.h"
#include "Parser.h"
#include "SymbolTable.h"

/* This implementation is not universal.
 * Because of the '@' at the beginning of the string, it appears to be an A-instruction.
 The string is read from the end to the second symbol.
 */
short string_to_decimal(const char *string, size_t const *length) {

    short temp, decimal;
    size_t digit_length;

    const short constant = 1;
    const short asciiZero = 48;
    digit_length = *length - 1;

    for (short decimal_units = 1; *(string + digit_length) != '@'; decimal_units *= 10, digit_length--) {
        temp = *(string + digit_length);
        temp = (temp - asciiZero) * (constant * decimal_units);
        decimal += temp;
    }

    return decimal;
}

char *_16bitsBinary_to_string(short * binary_value) {

    const char asciiZero = 48;
    static char arr[18];


    for (int j = 0; j < 16; ++j) {
        arr[j] = asciiZero + binary_value[j];
    }
    arr[16] = '\n';
    arr[17] = '\0';
    return arr;
}

void string_copy(char *to, char *from) {
    while ((*to++ = *from++));
}

void decimal_to_16bitsBinary(short const *decimal_num, short *const binary_instruction) {

    if (binary_instruction == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }

    short dividend = *decimal_num;
    short reminder;
    short divisor = 2;

    for (short i = BITS_16 - 1; i != -1; i--) {
        reminder = dividend % divisor;
        binary_instruction[i] = reminder;
        dividend = dividend / divisor;
    }

}

bool isDigit(char const *command) {

    if (*(command + 1) >= 48 && *(command + 1) <= 57)
        return true;

    return false;
}

void test_print_for_the_terminal(short const * binary_instruction) {
    // Print/Test for my terminal
    for (short i = 0; i < BITS_16; i++) {
        printf("%hu", binary_instruction[i]);
    }
    printf("\n");
}





