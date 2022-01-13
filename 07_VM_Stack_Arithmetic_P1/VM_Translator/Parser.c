//
// Created by Toor on 1/12/2022.
//

#include "Parser.h"

#define INPUT_LENGTH 127    //maximum allowed length of the input file line
#define MNEMONIC_LENGTH 14   //maximum allowed length of the mnemonic


void initializer(char const *input_file_dest, char const *output_file_dest) {

    FILE *input_file = NULL;
    FILE *output_file = NULL;

    char input_file_line[INPUT_LENGTH];

    input_file = fopen(input_file_dest, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open_asm_file %s\n", input_file_dest);
        exit(1);
    }

    output_file = fopen(output_file_dest, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Failed to open_asm_file %s\n", output_file_dest);
        exit(1);
    }

/* ----------------------> Action begins here <---------------------------*/

    while (hasMoreCommands(input_file_line, input_file) == true) {
        char *output = advance(input_file_line);
        if (output != NULL)
            fputs(output, output_file);
    }

/* -----------------------------------------------------------------------*/

    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
}


bool hasMoreCommands(char *input_file_line, FILE *file_in) {

    if (fgets(input_file_line, INPUT_LENGTH, file_in) != NULL)
        return true;

    return false;
}

char *advance(char *input_file_line) {

    char command[strlen(input_file_line)];
    char *command_type = NULL;
    char *mnemonic_arg1 = (char *) calloc(MNEMONIC_LENGTH, sizeof(*mnemonic_arg1));
    int *mnemonic_arg2 = (int *) calloc(1, sizeof(*mnemonic_arg2));

    //Cleaning the input_file_line of garbage. At the same time it checks if it's a real command
    if (reshape_theCommand(input_file_line, command) == true) {
        command_type = commandType(command);
    }

    // Proceeds to parse_arg1() for ALL command_types except "C_RETURN"
    if (strstr(command_type, "C_RETURN") == NULL) {
        parse_arg1(command, mnemonic_arg1);
        printf("%s\n", command);             // test print - remove me!
        printf("%s\n", mnemonic_arg1);       // test print - remove me!
    }

    // Proceeds to parse_arg2() ONLY for mentioned command_types
    if (strstr(command_type, "C_POP") || strstr(command_type, "C_PUSH") ||
        strstr(command_type, "C_FUNCTION") || strstr(command_type, "C_CALL")) {
        *mnemonic_arg2 = parse_arg2(command);
        printf("%d\n", *mnemonic_arg2);             // test print - remove me!
    }


    free(mnemonic_arg1);mnemonic_arg1 = NULL;
    free(mnemonic_arg2); mnemonic_arg2 = NULL;
    return "it Worked\n";
}


char *commandType(char *command) {

    if (strstr(command, "add") || strstr(command, "sub") || strstr(command, "neg") ||
        strstr(command, "and") || strstr(command, "or") || strstr(command, "not") ||
        strstr(command, "ea") || strstr(command, "gt") || strstr(command, "lt"))
        return "C_ARITHMETIC";

    else if (strstr(command, "push") != NULL)
        return "C_PUSH";

    else if (strstr(command, "pop") != NULL)
        return "C_POP";

    else if (strstr(command, "label") != NULL)
        return "C_LABEL";

    else if (strstr(command, "goto") != NULL)
        return "C_GOTO";

    else if (strstr(command, "if") != NULL)
        return "C_IF";

    else if (strstr(command, "function") != NULL)
        return "C_FUNCTION";

    else if (strstr(command, "return") != NULL)
        return "C_RETURN";

    else if (strstr(command, "call") != NULL)
        return "C_CALL";

    fprintf(stderr, "There is no such a command: %s", command);
    return NULL;

}

void parse_arg1(char const *command, char *dest_mnemonic) {

    while (*(command) != ' ' || !isDigit(command+1)) {
        *dest_mnemonic++ = *command++;
        if (*command == '\0')
            return;
    }
}

int parse_arg2(char const *command) {

    size_t command_tail = strlen(command) - 1;
    int digit_length = 0;

    //Count digit length in the command
    while (isDigit(command + command_tail--))
        digit_length++;

    //If no digits in the command, drop it!
    if (digit_length == 0) {
        fprintf(stderr, "Something went wrong parsing arg2: %s", command);
        return -1;
    }

    //Bringing tail to the initial length strlen(command)-1;
    command_tail += digit_length + 1;

    char temp[digit_length];

    for (int i = digit_length - 1; i >= 0; --i)
        temp[i] = *(command + command_tail--);

    temp[digit_length] = '\0';
    return string_to_decimal(temp);
}


bool reshape_theCommand(char const *fileInput, char *instruction) {

    if (*fileInput == '/' && *(fileInput + 1) == '/') return 0; //if any comments at the beginning
    if (*fileInput == '\r' || *fileInput == '\n') return 0;  //if any empty line at the beginning


    for (int i = 0, j = 0; *fileInput != '\0'; i++) {
        if (fileInput[i] == '\t') {   //if tabs or empty spaces
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