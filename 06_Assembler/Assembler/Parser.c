//
// Created by Toor on 9/16/2021.
//

#include "Parser.h"

static HashTable *label_symbols_hTable = NULL;
static HashTable *variable_symbols_hTable = NULL;

char *hasMoreCommands(char *lineFromFile, size_t const *arrLength) {

    char instruction[*arrLength];

    if (reshape_the_string(lineFromFile, instruction)) {
        size_t instruction_length = (size_t) strlen(instruction);
        return commandType(instruction, &instruction_length);
    }
    return NULL;
}

int reshape_the_string(char const *fileInput, char *instruction) {

    if (*fileInput == '/' && *(fileInput + 1) == '/') return 0; //if any comments at the beginning
    if (*fileInput == '\r' || *fileInput == '\n') return 0;  //if any empty line at the beginning


    for (int i = 0, j = 0; *fileInput != '\0'; i++) {
        if (fileInput[i] == '\t' || fileInput[i] == ' ') {   //if tabs or empty spaces
            instruction[i] = '\0';
            continue;
        } else if (fileInput[i] == '/' && fileInput[i + 1] == '/') { //if comments after the code
            instruction[j] = '\0';
            return 1;
        }

        instruction[j++] = fileInput[i];
        if (fileInput[i] == '\r' || fileInput[i] == '\t' || fileInput[i] == '\n') {
            instruction[--j] = '\0';
            if (*instruction == '\0') return 0;
            return 1;
        }
    }
    return 0;
}


char *commandType(char *instruction, size_t *length) {

    static short count_lines = 0;
    static short binary_instruction[BITS_16];

    // Create label_symbols table
    if (label_symbols_hTable == NULL)
        label_symbols_hTable = label_symbols();

    // Create variable_symbols table
    if (variable_symbols_hTable == NULL)
        variable_symbols_hTable = variable_symbols();


    //Label
    if (*instruction == '(') {
        handling_Label(instruction, length, count_lines, binary_instruction);
        return NULL;
    }

    //A_instruction
    if (*instruction == '@') {
        count_lines++;
        bool flag = handling_A_instruction(instruction, length, binary_instruction);
        if(flag == true) return _16bitsBinary_to_string(binary_instruction);
        return NULL;

        //C_instruction
    } else {
        count_lines++;
        handling_C_instruction(instruction, length, binary_instruction);
        return _16bitsBinary_to_string(binary_instruction);
    }
}


/* Label's value is equal to the next line number.*/
void handling_Label(char *key, size_t *length, short count_lines, short *binary_instruction) {

    short *value = &count_lines;

    // Removes the parenthesis '(' and ')' from the instruction
    if (*key == '(' && *(key + (*length) - 1) == ')') {
        for (int i = 0; i < *length; ++i) {
            if (i < *length - 2)key[i] = key[i + 1];
            else key[i] = '\0';
        }
    }

    *value = *value + 1;
    ht_insert(label_symbols_hTable, key, *value);
}


/*If symbol '@' is present, the function converts string value to a binary value */
bool handling_A_instruction(char *a_instruction, size_t *length, short *binary_instruction) {

    HashTableItem *symbol_item = NULL;
    HashTableItem *variable_item = NULL;
    static short variable_value = 16;
    short decimal_value = 0;

    //Handling Labels (ONLY "UPPER CASE"). a_instruction+1 is to skip '@' symbol
    if (*(a_instruction + 1) >= 65 && *(a_instruction + 1) <= 90) {

        // Take the value from the predefined symbol_table.
        symbol_item = ht_search(pre_defined_symbols(), a_instruction + 1);
        if (symbol_item != NULL) {
            short *pt = symbol_item->value;
            for (int i = 0; i < BITS_16; ++i) {
                binary_instruction[i] = pt[i];
            }

            // Print/Test for my terminal
            for (short i = 0; i < BITS_16; i++) {
                printf("%hu", binary_instruction[i]);
            }
            printf("\n");


            return true;
        }

        // If it's not a predefined symbol, then check the label_table for such a key.
        symbol_item = ht_search(label_symbols_hTable, a_instruction + 1);
        if (symbol_item != NULL) {
            short value = (short) symbol_item->value;
            decimal_to_16bitsBinary(&value, binary_instruction);

            // Print/Test for my terminal
            for (short i = 0; i < BITS_16; i++) {
                printf("%hu", binary_instruction[i]);
            }
            printf("\n");

            return true;

            /* If the key is not into the label_table, then add the key to the label_table with NULL value,
            so when later the (LABEL) is found, it's value will be updated. */
        } else if (symbol_item == NULL) {
            ht_insert(label_symbols_hTable, a_instruction + 1, NULL);
            return false;
        }

    }

        //Handling Variables (only "lower case"). a_instruction+1 is to skip '@' symbol
    else if (*(a_instruction + 1) >= 97 && *(a_instruction + 1) <= 122) {
        variable_item = ht_search(variable_symbols_hTable, a_instruction+1);
        if (variable_item != NULL) {
            short value = (short) variable_item->value;
            decimal_to_16bitsBinary(&value, binary_instruction);
            
            // Print/Test for my terminal
            for (short i = 0; i < BITS_16; i++) {
                printf("%hu", binary_instruction[i]);
            }
            printf("\n");
            
            return true;
        } else {
            ht_insert(variable_symbols_hTable, a_instruction+1, variable_value);
            ++variable_value;
            return false;
        }
    }

        //Handling Digits. a_instruction+1 is to skip '@' symbol
    else if (*(a_instruction + 1) >= 48 && *(a_instruction + 1) <= 57) {
        decimal_value = string_to_decimal(a_instruction, length);
        decimal_to_16bitsBinary(&decimal_value, binary_instruction);
        return true;
    } else {
        fprintf(stderr, "There is no such a-type instruction: %s", a_instruction+1);
    }


    // Print/Test for my terminal
    for (short i = 0; i < BITS_16; i++) {
        printf("%hu", binary_instruction[i]);
    }
    printf("\n");
    return false;

}


/*
 * Symbolic syntax: dest = comp ; jump
 * Binary syntax:  [16] = {1, 1, 1, a, c1, c2, c3, c4, c5, c6, d1, d2, d3, j1, j2, j3}
 * Example:        MD=D+1  1  1  1  0   0   1   1   1   1   1   0   1   1
 *                 D; JGT  1  1  1  0   0   0   1   1   0   0               0   0   1
 */
void handling_C_instruction(char *c_instruction, size_t *length, short *binary_instruction) {

    char key[*length + 1];
    bool flag = false;

//    /* Initialize first 3 MSB to 1 and the rest to 0 */
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
                HashTableItem *dest_item = ht_search(dest_instructions(), key);

                if (dest_item == NULL) {
                    fprintf(stderr, "There is no such c-type instruction: %s", key);
                    exit(0);
                }

                dest_parse(dest_item, binary_instruction);
                m = -1;

            } else if (c_instruction[i] == '\0') {
                key[m] = '\0';
                HashTableItem *comp_item = ht_search(comp_instructions(), key);

                if (comp_item == NULL) {
                    fprintf(stderr, "There is no such c-type instruction: %s", key);
                    exit(0);
                }

                comp_parse(comp_item, binary_instruction);
                m = -1;
            }

            //If c_instruction contains ';' symbol, then proceed with comp and jump bits
        } else if (!flag) {
            if (c_instruction[i] == ';') {
                key[m] = '\0';
                HashTableItem *comp_item = ht_search(comp_instructions(), key);

                if (comp_item == NULL) {
                    fprintf(stderr, "There is no such c-type instruction: %s", key);
                    exit(0);
                }

                comp_parse(comp_item, binary_instruction);
                m = -1;

            } else if (c_instruction[i] == '\0') {
                key[m] = '\0';
                HashTableItem *jump_item = ht_search(jump_instructions(), key);

                if (jump_item == NULL) {
                    fprintf(stderr, "There is no such c-type instruction: \"%s\"", key);
                    exit(0);
                }

                jmp_parse(jump_item, binary_instruction);
                m = -1;
            }
        } else {
            fprintf(stderr, "There is no such c-type instruction: \"%s\"", key);
            exit(0);
        }
    }

    // Print/Test for my terminal
    for (int k = 0; k < 16; ++k) {
        printf("%d", binary_instruction[k]);
    }
    printf("\n");

}



