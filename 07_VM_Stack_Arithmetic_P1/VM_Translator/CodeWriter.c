//
// Created by Toor on 1/12/2022.
//

#include "CodeWriter.h"

#define C_LENGTH 60 //MAXIMUM possible length of the string

void setFileName(char *fileName) {

}


char *writeInit() {

    return writeFunctions("C_INIT", NULL, NULL);
}


char *writeDelegator(char *command_type, char *arg1, char *arg2, char const *file_name) {

    //PUSH or POP
    if (strcmp(command_type, "C_PUSH") == 0 || strcmp(command_type, "C_POP") == 0) {
        return writePushPop(command_type, arg1, arg2, file_name);
    }

        // FUNCTION
    else if (strcmp(command_type, "C_FUNCTION") == 0 || strcmp(command_type, "C_CALL") == 0 ||
             strcmp(command_type, "C_RETURN") == 0) {
        return writeFunctions(command_type, arg1, arg2);
    }

        // ARITHMETIC
    else if (strcmp(command_type, "C_ARITHMETIC") == 0) {
        return writeArithmetic(arg1);
    }

        // Branching
    else if (strcmp(command_type, "C_LABEL") == 0 || strcmp(command_type, "C_GOTO") == 0 ||
             strcmp(command_type, "C_IF") == 0) {
        return writeBranching(command_type, arg1);
    }

    return NULL;
}


char *writePushPop(char *command_type, char *arg1, char *arg2, char const *file_name) {

    //Push
    if (strstr(command_type, "C_PUSH")) {
        return push_memory_access_segments(arg1, arg2, file_name);
    }
        //Pop
    else if (strstr(command_type, "C_POP")) {
        return pop_memory_access_segments(arg1, arg2, file_name);
    }

    return NULL;
}


char *writeArithmetic(char *command) {
    return arithmetic_segments(command);
}


char *writeBranching(char *arg1, char *arg2) {
    return branching_commands(arg1, arg2);
}


char *writeFunctions(char *command_type, char *arg1, char *arg2) {
    return function_commands(command_type, arg1, arg2);
}

