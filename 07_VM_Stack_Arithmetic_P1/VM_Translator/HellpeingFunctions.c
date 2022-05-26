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

// This initializer works the same way as does the one from Parser file, only this one can read files from directories
void initializer_dir(char const *input_file_dest, char const *output_file_dest) {

    DIR *input_dir = opendir(input_file_dest);
    FILE *input_file = NULL;
    FILE *output_file = NULL;

    char input_file_line[INPUT_LENGTH];
    char *input_file_name = NULL;
    struct dirent *de;


    if (input_dir == NULL) {
        printf("Could not open current directory");
        exit(1);
    }

    output_file = fopen(output_file_dest, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Failed to open_asm_file %s\n", output_file_dest);
        exit(1);
    }

    //Bootstrap Code
    fputs(writeInit(), output_file);

    while ((de = readdir(input_dir)) != NULL) {

        if (strstr(de->d_name, ".vm") != NULL) {
            printf("%s\n", de->d_name);
            input_file_name = (char *) calloc(200, sizeof(*input_file_name));

            strcat(input_file_name, input_file_dest);
            strcat(input_file_name, "\\");
            strcat(input_file_name, de->d_name);

            input_file = fopen(input_file_name, "r");
            if (input_file == NULL) {
                fprintf(stderr, "Failed to open_asm_file %s\n", input_file_dest);
                exit(1);
            }

/* ----------------------> Action begins here <---------------------------*/
            while (hasMoreCommands(input_file_line, input_file) == true) {
                char *output = advance(input_file_line, input_file_dest);
                if (output != NULL) {
                    fputs(output, output_file);
                }

            }
/* -----------------------------------------------------------------------*/
            fclose(input_file);
            input_file = NULL;
            free(input_file_name);
            input_file_name = NULL;
        }

    }
    fclose(output_file);
    output_file = NULL;
    closedir(input_dir);

}






