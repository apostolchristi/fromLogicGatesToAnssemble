//
// Created by Toor on 1/12/2022.
//

#include "CodeWriter.h"

#define C_LENGTH 60 //MAXIMUM possible length of the string


char *writePushPop(char *mnemonic_arg1, char *mnemonic_arg2, char const *file_name) {

    //Push
    if (strstr(mnemonic_arg1, "push")) {
        return push_memory_access_segments(mnemonic_arg1, mnemonic_arg2, file_name);
    }
        // Pop
    else if (strstr(mnemonic_arg1, "pop")) {
        return pop_memory_access_segments(mnemonic_arg1, mnemonic_arg2, file_name);

    }

    return NULL;
}

char *writeArithmetic(char *mnemonic_arg1) {

    return arithmetic_segments(mnemonic_arg1, NULL, NULL);
}


char *writeBranching(char *mnemonic_arg1, char *mnemonic_arg2) {

   return branching_commands(mnemonic_arg1,mnemonic_arg2);
}


char *writeFunctions(char *mnemonic_arg1, char *mnemonic_arg2) {

return function_commands(mnemonic_arg1, mnemonic_arg2);
}









