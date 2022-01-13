//
// Created by Toor on 9/22/2021.
//

#include "HellpeingFunctions.h"
#include "Parser.h"

int string_to_decimal(const char *string) {
    const short constant = 1;
    const short asciiZero = 48;
    int temp = 0, decimal = 0;
    int digit_length = (int) strlen(string) - 1;

    for (int decimal_units = 1; digit_length >= 0; decimal_units *= 10, digit_length--) {
        temp = *(string + digit_length);
        temp = (temp - asciiZero) * (constant * decimal_units);
        decimal += temp;
    }

    return decimal;
}


bool isDigit(char const *command) {

    if (*command >= 48 && *command <= 57)
        return true;

    return false;
}







