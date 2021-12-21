//
// Created by Toor on 11/24/2021.
//

#include "Parser.h"

#include "Parser.h"

#define INPUT_LENGTH 127    //maximum allowed length of the input file line
#define MNEMONIC_LENGTH 4   //maximum allowed length of the mnemonic

static short binary_instruction[BITS_16];   //it keeps the processed binary instructions from mnemonics or commands
static short count_lines;                   //it count lines in the file, so a (LABEL) could jump to the right address. Keep in mind it jumps to the next address so count_lines+1 is required
static short variable_value;                //variables begin their counting from address #16
static char label_processing_flag;          //first time the file is parsed only for (LABELS), and only from the second parse we process everything else. So it's a flag for that.

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
    constructor_Parser();

    while (hasMoreCommands(input_file_line, input_file) == true) {
        char *output = advance(input_file_line);
        if (output != NULL)
            fputs(output, output_file);
    }

    destructor_Parser();
/* -----------------------------------------------------------------------*/

    fclose(input_file);
    fclose(output_file);
    input_file = NULL;
    output_file = NULL;
}

bool hasMoreCommands(char *input_file_line, FILE *file_in) {

    if (fgets(input_file_line, INPUT_LENGTH, file_in) != NULL)
        return true;

    //Points the beginning of the file, so the process of mnemonics and commands could be parsed
    if (label_processing_flag == 0) {
        fseek(file_in, 0, SEEK_SET);
        *input_file_line = '\0';
        label_processing_flag = 1;
        return true;
    }

    return false;
}

void constructor_Parser() {

    //Initialize all binary values to 0
    for (int i = 0; i < BITS_16; ++i)
        binary_instruction[i] = 0;

    count_lines = 0;
    variable_value = 16;
    label_processing_flag = 0;
}

void destructor_Parser() {

    destructor_SymbolTable();
    destructor_Code();
}


char *advance(char *input_file_line) {

    char command[strlen(input_file_line)];
    size_t command_length;
    char command_type;
    char *mnemonic = calloc(MNEMONIC_LENGTH, sizeof(*mnemonic));

    //Cleaning the input_file_line of garbage. At the same time it checks if it's a real command
    if (reshape_theCommand(input_file_line, command) == true) {
        command_length = strlen(command);
        command_type = *commandType(command);

        /* When label_processing_flag = 0 then we parse only (LABELS) and skip the A and C commands.
         * But when it finished and becomes label_processing_flag = 1 then we skip (LABELS) and parse only A and C commands */
        if ((label_processing_flag == 0 && command_type != 'L') ||
            (label_processing_flag == 1 && command_type == 'L')) {
            return NULL;
        }

        switch (command_type) {
            case 'A':
                //Handling Digits
                if (isDigit(command)) {
                    short decimal_value = string_to_decimal(command, &command_length);
                    decimal_to_16bitsBinary(&decimal_value, binary_instruction);
                    test_print_for_the_terminal(binary_instruction);    //can be removed
                    return _16bitsBinary_to_string(binary_instruction);
                }
                //Handling @variables and @PREDEFINED_LABELS parsed from (LABELS)
                else {
                    addEntry(command + 1, variable_value++, binary_instruction);
                    test_print_for_the_terminal(binary_instruction);    //can be removed
                    return _16bitsBinary_to_string(binary_instruction);
                }

            case 'C':
                // Initialize first 3 MSB to 1
                for (int i = 0; i < 3; ++i)
                    binary_instruction[i] = 1;

                if (strchr(command, '=') != NULL) {
                    parse_dest(command, mnemonic);
                    dest_instructions(binary_instruction, mnemonic);
                    parse_comp(command, mnemonic);
                    comp_instructions(binary_instruction, mnemonic);
                    test_print_for_the_terminal(binary_instruction);    //can be removed
                    return _16bitsBinary_to_string(binary_instruction);
                } else {
                    parse_comp(command, mnemonic);
                    comp_instructions(binary_instruction, mnemonic);
                    parse_jump(command, mnemonic);
                    jmp_instructions(binary_instruction, mnemonic);
                    test_print_for_the_terminal(binary_instruction);    //can be removed
                    return _16bitsBinary_to_string(binary_instruction);
                }

            case 'L':
                parse_symbols(command, &command_length);
                addEntry(command, count_lines + 1, binary_instruction);
                break;

            default:
                return NULL;
        }
    }

    free(mnemonic);
    return NULL;
}


char *commandType(char *command) {

    if (strchr(command, '@') != NULL) {
        count_lines++;
        return "A_COMMAND";
    } else if (strchr(command, '=') != NULL || strchr(command, ';') != NULL) {
        count_lines++;
        return "C_COMMAND";
    } else if (strchr(command, '(') != NULL && strchr(command, ')') != NULL)
        return "L_COMMAND";


    fprintf(stderr, "There is no such a command: %s", command);
    return "null";
}


void parse_symbols(char *command, size_t *length) {

    if (*command == '(' && *(command + *(length) - 1) == ')') {
        for (int i = 0; i < *length; ++i) {
            if (i < *length - 2)
                command[i] = command[i + 1];
            else command[i] = '\0';
        }
    }
}


void parse_dest(char const *command, char *dest_mnemonic) {

    while (*command != '=')
        *dest_mnemonic++ = *command++;
}


void parse_comp(char const *command, char *comp_mnemonic) {

    if (strchr(command, '=') != NULL) {
        for (size_t i = strlen(command) - 1; command[i] != '='; --i) {
            *comp_mnemonic = command[i];
        }
        *(comp_mnemonic + 1) = '\0';
    } else {
        while (*command != ';')
            *comp_mnemonic++ = *command++;
    }
}


void parse_jump(char const *command, char *jmp_mnemonic) {

    for (size_t i = 0; i < strlen(strchr(command, ';')) - 1; ++i)
        *jmp_mnemonic++ = *(strchr(command, ';') + i + 1);
}

bool reshape_theCommand(char const *fileInput, char *instruction) {

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

