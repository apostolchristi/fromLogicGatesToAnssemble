//
// Created by Toor on 1/12/2022.
//

#include "CodeWriter.h"

#define C_LENGTH 60 //MAXIMUM possible length of the string


char *memoryAccessSegmentType(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name) {

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







