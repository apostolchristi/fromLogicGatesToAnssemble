//
// Created by Toor on 1/12/2022.
//

#include "Parser.h"

#define INPUT_LENGTH 127    //maximum allowed length of the input file line
#define ARG1_LENGTH 14   //maximum allowed length of the mnemonic
#define C_LENGTH 60         //MAXIMUM possible length of the string
#define COMMAND_LENGTH 8      //Maximum allowed length of the command

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

    //Bootstrap Code
    fputs(writeInit(), output_file);
/* ----------------------> Action begins here <---------------------------*/
    while (hasMoreCommands(input_file_line, input_file) == true) {
        char *output = advance(input_file_line, input_file_dest);
        if (output != NULL) {
            fputs(output, output_file);
        }

    }
/* -----------------------------------------------------------------------*/
    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
}


bool hasMoreCommands(char *input_file_line, FILE *file_in) {

    if (fgets(input_file_line, INPUT_LENGTH, file_in) != NULL) {
        return true;
    }
    return false;
}


char *advance(char *input_file_line, char const *input_file_name) {

    char command[strlen(input_file_line)];
    char *command_type = NULL;
    char *assembly = NULL;
    char *arg1 = (char *) calloc(ARG1_LENGTH, sizeof(*arg1));
    char *arg2 = NULL;


    //Cleaning the input_file_line of garbage. At the same time it checks if it's a real command
    if (reshape_theCommand(input_file_line, command) == true) {
        command_type = commandType(command);
    } else {
        return assembly;
    }

    // Proceeds to parse_arg1() for ALL command_types except "C_RETURN"
    if (strcmp(command_type, "C_RETURN") != 0) {
        parse_arg1(command, command_type, arg1);
    }
    // Proceeds to parse_arg2() ONLY for mentioned command_types
    if (strcmp(command_type, "C_POP") == 0 || strcmp(command_type, "C_PUSH") == 0 ||
        strcmp(command_type, "C_FUNCTION") == 0 || strcmp(command_type, "C_CALL") == 0) {
        arg2 = parse_arg2(command);
    }

    assembly = writeDelegator(command_type, arg1, arg2, input_file_name);
    assembly = add_comments(command, assembly);

    free(arg1);arg1 = NULL;
    free(arg2);arg2 = NULL;

    return assembly;
}


char *commandType(char *command) {

    char *command_type = calloc(COMMAND_LENGTH, sizeof(*command_type));

    //Copy initial command up to the ' ' = "space"
    for (int i = 0; *command != ' '; ++i) {
        *(command_type + i) = *command++;
    }

    if (strstr(command_type, "add") != NULL || strstr(command_type, "sub") != NULL ||
        strstr(command_type, "neg") != NULL || strstr(command_type, "and") != NULL ||
        strstr(command_type, "or") != NULL || strstr(command_type, "not") != NULL ||
        strstr(command_type, "eq") != NULL || strstr(command_type, "gt") != NULL ||
        strstr(command_type, "lt") != NULL )  {
//        free(command_type);
        return "C_ARITHMETIC";
    } else if (strstr(command_type, "push") != NULL) {
        free(command_type);
        return "C_PUSH";
    } else if (strstr(command_type, "pop") != NULL) {
        free(command_type);
        return "C_POP";
    } else if (strstr(command_type, "label") != NULL) {
        free(command_type);
        return "C_LABEL";
    } else if (strstr(command_type, "if") != NULL) {
        free(command_type);
        return "C_IF";
    } else if (strstr(command_type, "goto") != NULL) {
        free(command_type);
        return "C_GOTO";
    } else if (strstr(command_type, "function") != NULL) {
        free(command_type);
        return "C_FUNCTION";
    } else if (strstr(command_type, "return") != NULL) {
//        free(command_type);
        return "C_RETURN";
    } else if (strstr(command_type, "call") != NULL) {
        free(command_type);
        return "C_CALL";
    }

    fprintf(stderr, "There is no such a command: %s", command_type);
    return NULL;
}

void parse_arg1(char const *command, char const *command_type, char *arg1) {

    if(strcmp(command_type, "C_ARITHMETIC") == 0) {
        strcpy(arg1, command);
        return;
    }

    char *temp_arg1 = strstr(command, " ");
    if(*temp_arg1 == ' ')
        temp_arg1++;

    while (*(temp_arg1) != ' ' || !isDigit(temp_arg1 + 1)) {
        *arg1++ = *temp_arg1++;
        if (*temp_arg1 == '\0')
            return;
    }
}

char *parse_arg2(char const *command) {

    size_t command_tail = strlen(command) - 1;
    int digit_length = 0;

    //Count digit length in the command
    while (isDigit(command + command_tail--)) {
        digit_length++;
    }

    //If no digits in the command, drop it!
    if (digit_length == 0) {
        fprintf(stderr, "Something went wrong with the command %s\n", command);
        return NULL;
    }

    char *arg2 = calloc(digit_length + 2, sizeof(*arg2));

    //Bringing tail to the initial length strlen(command)-1;
    command_tail += digit_length + 1;

    for (int i = digit_length - 1; i >= 0; --i)
        arg2[i] = *(command + command_tail--);

    arg2[digit_length] = '\n';
    arg2[digit_length + 1] = '\0';

    return arg2;
}


bool reshape_theCommand(char const *fileInput, char *instruction) {

    if (*fileInput == '/' && *(fileInput + 1) == '/') return 0; //if any comments at the beginning
    if (*fileInput == '\r' || *fileInput == '\n') return 0;  //if any empty line at the beginning


    for (int i = 0, j = 0; *fileInput != '\0'; i++) {
        if (fileInput[i] == '\t') {   // if tabs
            instruction[i] = '\0';
            continue;
        } else if (fileInput[i] == '/' && fileInput[i + 1] == '/') { // if comments after the code
            instruction[j] = '\0';
            return 1;
        } else if (fileInput[i] == ' ' && fileInput[i+1] == ' ') { // if 2 spaces after the code
            instruction[j] = '\0';
            return 1;
        }

        instruction[j++] = fileInput[i];
        if (fileInput[i] == '\r' || fileInput[i] == '\t' || fileInput[i] == '\n'){
            instruction[--j] = '\0';
            if (*instruction == '\0') return 0;
            return 1;
        }
    }
    return 0;
}

char *add_comments(char *current_command, char *segment_assembly_code) {

    char *assembly = calloc(C_LENGTH, sizeof(*assembly));
    strcat(assembly, "// ");
    strcat(assembly, current_command);
    strcat(assembly, "\n");

    strcat(assembly, segment_assembly_code);
    *(assembly + strlen(assembly)) = '\0';

    return assembly;
}
