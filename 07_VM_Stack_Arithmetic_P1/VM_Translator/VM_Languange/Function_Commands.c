//
// Created by Toor on 2/2/2022.
//

#include "Function_Commands.h"

#define C_LENGTH 100 //MAXIMUM possible length of the string
char *function_assembly_code = NULL;


char *function_commands(char *mnemonic_arg1, char *mnemonic_arg2) {

    function_assembly_code = calloc(C_LENGTH, sizeof(*function_assembly_code));

    //Call
    if (strstr(mnemonic_arg1, "label")) {
        writeCall(mnemonic_arg1, mnemonic_arg2);
    }
    
    return function_assembly_code;
}


void writeCall(char *functionName, int numArgs) {

}
