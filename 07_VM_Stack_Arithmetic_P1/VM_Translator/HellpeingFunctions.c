//
// Created by Toor on 9/22/2021.
//

#include "HellpeingFunctions.h"
#include "Parser.h"

#define BITS_16 16 /* max array length */


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

char *decimal_to_string(int *decimal) {

    char *the_string = (char *) calloc(6, sizeof(*the_string));

    sprintf(the_string, "%d", *decimal);

    return the_string;
}


bool isDigit(char const *command) {

    if (*command >= 48 && *command <= 57)
        return true;

    return false;
}


bool get_basename_of_theFile(char const *fileInput, char *instruction) {

    if (*fileInput == '/' && *(fileInput + 1) == '/') return 0; //if any comments at the beginning
    if (*fileInput == '\r' || *fileInput == '\n') return 0;  //if any empty line at the beginning


    for (int i = 0, j = 0; *fileInput != '\0'; i++) {
        if (fileInput[i] == '\t') {   //if tabs
            instruction[i] = '\0';
            continue;
        } else if (fileInput[i] == '/' && fileInput[i + 1] == '/') { //if comments after the code
            instruction[j] = '\0';
            return 1;
        } else if (fileInput[i] == '\\') {
            instruction[i] = '\0';
            continue;
        }

        instruction[j++] = fileInput[i];
        if (fileInput[i] == '\r' || fileInput[i] == '\t' || fileInput[i] == '\n' || fileInput[i] == '.') {
            instruction[j] = '\0';
            if (*instruction == '\0') return 0;
            return 1;
        }
    }
    return 0;
}






