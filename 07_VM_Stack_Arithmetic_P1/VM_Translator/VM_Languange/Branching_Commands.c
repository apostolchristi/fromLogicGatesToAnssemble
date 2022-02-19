//
// Created by Toor on 2/2/2022.
//

#include "Branching_Commands.h"
#define C_LENGTH 100 //MAXIMUM possible length of the string

char *branching_assembly_code = NULL;

char *branching_commands(char *mnemonic_arg1, char *mnemonic_arg2) {

    branching_assembly_code = calloc(C_LENGTH, sizeof(*branching_assembly_code));

    //label
    if (strstr(mnemonic_arg1, "label")) {
       writeLabel(mnemonic_arg2);
    }

    //if_goto
    else if (strstr(mnemonic_arg1, "if")) {
        writeIf(mnemonic_arg2);
    }

    //goto
    else if (strstr(mnemonic_arg1, "goto")) {
       writeGoto(mnemonic_arg2);
    }

    return branching_assembly_code;
}

// (LABEL)
void writeLabel(char *mnemonic_arg2) {

    *branching_assembly_code = '(';
    strcat(branching_assembly_code, mnemonic_arg2);
    strcat(branching_assembly_code, ")\n");
}

// @LABEL
// jump
void writeGoto(char *mnemonic_arg2) {

    *branching_assembly_code = '@';
    strcat(branching_assembly_code, mnemonic_arg2);
    strcat(branching_assembly_code, "\n"
                                    "0;JMP\n");
}

// SP--
// if true(-1) then jump to @LABEL
void writeIf(char *mnemonic_arg2) {

    char *assembly_if = "@SP\n"
                        "AM=M-1\n"
                        "D=M\n@";
    strcat(branching_assembly_code, assembly_if);
    strcat(branching_assembly_code, mnemonic_arg2);
    strcat(branching_assembly_code, "\nD;JNE\n");
}