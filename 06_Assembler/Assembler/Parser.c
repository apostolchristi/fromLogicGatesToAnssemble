//
// Created by Toor on 9/16/2021.
//

#include "Parser.h"


char *hasMoreCommands(char *lineFromFile, size_t const *arrLength) {

    char instruction[*arrLength];

    if (reshape_the_string(lineFromFile, instruction)) {
        size_t instruction_length = (size_t)strlen(instruction);
        return commandType(instruction, &instruction_length);
    }
    return NULL;
}

int reshape_the_string(char const *fileInput, char *instruction) {

    for (int i = 0; *fileInput != '\0'; i++) {
        if (fileInput[i] == '/' && fileInput[i + 1] == '/') {   //if any comments
            return 0;
        } else if (fileInput[i] == '\r' && i == 0) {      //if any empty line
            return 0;
        }

        instruction[i] = fileInput[i];
        if (fileInput[i] == '\r' || fileInput[i] == '\t') {
            instruction[i] = '\0';
            return 1;
        }
    }
}

char *commandType(char *instruction, size_t *length) {

    static short binary_instruction[BITS_16];

    if (*instruction == '@') {
       handling_A_instruction(instruction, length, binary_instruction);
        return _16bitsBinary_to_string(binary_instruction);

    } else {
        handling_C_instruction(instruction, length, binary_instruction);
        return _16bitsBinary_to_string(binary_instruction);
    }
}

/*If symbol '@' is present, it converts the decimal value to a binary value */
void handling_A_instruction(char *a_instruction, size_t *length, short *binary_instruction) {

    short decimal_value;

    decimal_value = string_to_decimal(a_instruction, length);
    decimal_to_16bitsBinary(&decimal_value, binary_instruction);

    // Print/Test for my terminal
    for (short i = 0; i < BITS_16; i++) {
        printf("%hu", binary_instruction[i]);
    }
    printf("\n");

}


/*
 * Symbolic syntax: dest = comp ; jump
 * Binary syntax:  [16] = {1, 1, 1, a, c1, c2, c3, c4, c5, c6, d1, d2, d3, j1, j2, j3}
 * Example:        MD=D+1  1  1  1  0   0   1   1   1   1   1   0   1   1
 *                 D; JGT  1  1  1  0   0   0   1   1   0   0               0   0   1
 */
void handling_C_instruction(char *c_instruction, size_t *length,short *binary_instruction) {

    char key[*length + 1];
    bool flag = false;

//    /* Initialize first 3 MSB bits to 1 and the rest to 0*/
    for (int i = 0; i < BITS_16; ++i) {
        if (i < 3) binary_instruction[i] = 1;
        else binary_instruction[i] = 0;
    }

    if (strchr(c_instruction, '=') != NULL)
        flag = true;

    for (int i = 0, m = 0; i <= *length; i++, m++) {
        key[m] = c_instruction[i];

        //If c_instruction contains '=' symbol, then proceed with dest and comp bits
        if (flag) {
            if (c_instruction[i] == '=') {
                key[m] = '\0';
                dest_parse(ht_search(dest_instructions(), key), binary_instruction);
                m = -1;

            } else if (c_instruction[i] == '\0') {
                key[m] = '\0';
                comp_parse(ht_search(comp_instructions(), key), binary_instruction);
                m = -1;
            }

        //If c_instruction contains ';' symbol, then proceed with comp and jump bits
        } else if (!flag) {
            if (c_instruction[i] == ';') {
                key[m] = '\0';
                comp_parse(ht_search(comp_instructions(), key), binary_instruction);
                m = -1;

            } else if (c_instruction[i] == '\0') {
                key[m] = '\0';
                jmp_parse(ht_search(jump_instructions(), key), binary_instruction);
                m = -1;
            }
        }
    }

    // Print/Test for my terminal
    for (int k = 0; k < 16; ++k) {
        printf("%d", binary_instruction[k]);
    }
    printf("\n");

}



