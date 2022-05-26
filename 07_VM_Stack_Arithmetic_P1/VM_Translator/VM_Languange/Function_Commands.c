//
// Created by Toor on 2/2/2022.
//

#include "Function_Commands.h"

#define C_LENGTH 500 //MAXIMUM possible length of the string
char *function_assembly_code = NULL;
char *returnAddress = NULL;
char *endFrame = NULL;




char *function_commands(char *command_type, char *arg1, char *arg2) {
    function_assembly_code = calloc(C_LENGTH, sizeof(*function_assembly_code));


    //Call
    if (strcmp(command_type, "C_CALL") == 0) {
        writeCall(arg1, arg2);
    }

    else if (strcmp(command_type, "C_FUNCTION") == 0) {
        writeFunction(arg1, arg2);
    }

    else if (strcmp(command_type, "C_RETURN") == 0) {
        writeReturn(arg1);
    }

    else if (strcmp(command_type, "C_INIT") == 0) {
        bootstrap();
    }

    return function_assembly_code;
}

void bootstrap() {

    // Initialize the stack pointer to 0x0100 (SP= 256)
    strcat(function_assembly_code, "@256\nD=A\n@SP\nM=D\n");

    // Start executing (the translated code of) Sys.init
    writeCall("Sys.init", "0");
}

/*
 push returnAddress
 push LCL
 push ARG
 push THIS
 push THAT
 ARG = SP - 5 - nArgs
 LCL = SP
 goto functionName
 */

void writeCall(char *functionName, char *nArgs) {

    returnAddress = calloc(100, sizeof(*returnAddress));
    endFrame = calloc(100, sizeof(*endFrame));

    strcat(returnAddress, "retAddr_");
    strcat(returnAddress, functionName);

    strcat(endFrame, "@endFrame_");
    strcat(endFrame,functionName);



    //push (returnAddress) : Using the label declared below
    strcat(function_assembly_code, "@");
    strcat(function_assembly_code, returnAddress);
    char *assembly_call_p1 =
            "\nD=A\n"
            "@SP\n"
            "A=M\n"
            "M=D\n"

            //push LCL : Save LCL of the caller
            "@LCL\n"
            "D=M\n"
            "@SP\n"
            "AM=M+1\n"
            "M=D\n";

    strcat(function_assembly_code, assembly_call_p1);
    char *assembly_call_p2 =

            //push ARG: Save ARG of the caller
            "@ARG\n"
            "D=M\n"
            "@SP\n"
            "AM=M+1\n"
            "M=D\n"

            //push THIS: Save THIS of the caller
            "@THIS\n"
            "D=M\n"
            "@SP\n"
            "AM=M+1\n"
            "M=D\n"

            //push THAT: Save THAT of the caller
            "@THAT\n"
            "D=M\n"
            "@SP\n"
            "AM=M+1\n"
            "M=D\n"

            //ARG = SP-5-nArgs: Reposition ARG
            "D=A\n"
            "@R4\n"
            "D=D-A\n"
            "@SP\n"
            "AM=M+1\n"
            "M=D\n@";
    strcat(function_assembly_code, assembly_call_p2);
    strcat(function_assembly_code, nArgs);
    char *assembly_call_p3 =
            "\nD=A\n"
            "@SP\n"
            "A=M\n"
            "D=M-D\n"
            "M=0\n"
            "@ARG\n"
            "M=D\n"

            //LCL = SP: Reposition LCL  - so from here I start to push the local variables
            "@SP\n"
            "A=M\n"
            "D=A\n"
            "@LCL\n"
            "M=D\n@";
    strcat(function_assembly_code, assembly_call_p3);

    //goto functionName: Transfers control to the called function
    strcat(function_assembly_code, functionName);
    strcat(function_assembly_code, "\n0;JMP\n(");

    // (returnAddress): Declares a label for the return-address
    strcat(function_assembly_code, returnAddress);
    strcat(function_assembly_code, ")\n\n");

}

/*
(functionName)
repeat nParam times
push 0
 */
void writeFunction(char *functionName, char *nArgs) {

    char *var_loop__name = calloc(100, sizeof(*var_loop__name));
    strcat(var_loop__name, "@nArgs_");
    strcat(var_loop__name, functionName);


    // (functionName) : Declares a label for the function entry
    *function_assembly_code = '(';
    strcat(function_assembly_code, functionName);
    strcat(function_assembly_code, ")\n@");

    // repeat nParam times : nParam = Nr. of local variables
    // push 0 : Initializes the local variables to 0
    strcat(function_assembly_code, nArgs);
    strcat(function_assembly_code, "D=A\n");
    strcat(function_assembly_code, var_loop__name);
    strcat(function_assembly_code, "\nM=D\n(LOOP_");
    strcat(function_assembly_code, functionName);
    char *assembly_function_p1 =
            ")\n"
            "@SP\n"
            "A=M\n"
            "M=0\n"
            "@SP\n"
            "M=M+1\n";
    strcat(function_assembly_code, assembly_function_p1);
    strcat(function_assembly_code, var_loop__name);
    strcat(function_assembly_code, "\nMD=M-1\n@LOOP_");
    strcat(function_assembly_code, functionName);
    strcat(function_assembly_code, "\nD;JGT\n\n");

    free(var_loop__name);
    var_loop__name = NULL;
}

/*
 endFrame = LCL
 retAddr = *(endFrame-5)
 *ARG = pop()
 SP = ARG+1
 THAT = *(endFrame - 1)
 */
void writeReturn(char *functionName) {


// endFrame = LCL : Is a temporary variable
    strcat(function_assembly_code, "@LCL\nD=M\n");
    strcat(function_assembly_code, endFrame);
    strcat(function_assembly_code, "\nM=D\n");

    // retAddr = *(endFrame-5) : Gets the return address
    strcat(function_assembly_code,"@R5\nD=D-A\n@");
    strcat(function_assembly_code, returnAddress);
    strcat(function_assembly_code, "\nM=D\n");

    char *assembly_return_p1 =
            // *ARG = pop() : Repositions the return value for the caller
            "@SP\n"
            "AM=M-1\n"
            "D=M\n"
            "@ARG\n"
            "A=M\n"
            "M=D\n"

            // SP = ARG+1 : Repositions SP of the caller
            "@ARG\n"
            "D=M\n"
            "@SP\n"
            "M=D+1\n";
    strcat(function_assembly_code, assembly_return_p1);

    //  THAT = *(endFrame - 1) : Restore THAT of the caller
    strcat(function_assembly_code, endFrame);
    strcat(function_assembly_code,"\nA=M-1\nD=M\n@THAT\nM=D\n" );

    // THIS = *(endFrame - 2) : Restore THIS of the caller
    strcat(function_assembly_code, endFrame);
    strcat(function_assembly_code, "\nAM=M-1\nD=M\n@THIS\nM=D\n");

    //ARG = *(endFrame - 3) : Restore ARG of the caller
    strcat(function_assembly_code, endFrame);
    strcat(function_assembly_code, "\nAM=M-1\nD=M\n@ARG\nM=D\n");

    //LCL = *(endFrame - 4) : Restore LCL of the caller
    strcat(function_assembly_code, endFrame);
    strcat(function_assembly_code, "\nAM=M-1\nD=M\n@LCL\nM=D\n@");

    // goto retAddr : goes to return address in the caller's code
    strcat(function_assembly_code, returnAddress);
    strcat(function_assembly_code, "\n0;JMP\n");

}
