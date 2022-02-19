//
// Created by Toor on 2/2/2022.
//

#include "Memory_Access_Comands.h"

#define C_LENGTH 60 //MAXIMUM possible length of the string

char *segment_type = NULL;
char *assembly_code = NULL;

/* Concatenates to '@' the mnemonic_arg2.
 Assembly ex: "@42" 42 came from the VM "push constant 42" command.
 */
void init_assembly_string(char *mnemonic_arg1, char *mnemonic_arg2) {

    assembly_code = calloc(C_LENGTH, sizeof(*assembly_code));

    //Initiate the assembly_code string to some condition, except when it is a "pointer" && "static" instruction
    if (!strstr(mnemonic_arg1, "pointer") && !strstr(mnemonic_arg1, "static")) {
        *assembly_code = '@';
        strcat(assembly_code, mnemonic_arg2);
    }
}


char *push_memory_access_segments(char *mnemonic_arg1, char *mnemonic_arg2, char const *file_name) {

    init_assembly_string(mnemonic_arg1, mnemonic_arg2);

        //Constant_Segment
    if (strstr(mnemonic_arg1, "constant")) {
        push_constant_segment();
        return assembly_code;
    }

        //Pointer_Segment
    else if (strstr(mnemonic_arg1, "pointer")) {
        push_pointer_segment(mnemonic_arg2);
        return assembly_code;
    }

        //Static_Segment
    else if (strstr(mnemonic_arg1, "static")) {
        push_static_segment(file_name, mnemonic_arg2);
        return assembly_code;
    }

        //Temp_Segment
    else if (strstr(mnemonic_arg1, "temp")) {
        push_temp_segment();
        return assembly_code;
    }

        //Segment_pointers: LCL, ARG, THIS, THAT
    else if (((segment_type = strstr(mnemonic_arg1, "local")) ||
              (segment_type = strstr(mnemonic_arg1, "argument")) ||
              (segment_type = strstr(mnemonic_arg1, "this")) || (segment_type = strstr(mnemonic_arg1, "that")))) {
        substitute(&segment_type);
        push_segment_pointers(segment_type);
        return assembly_code;
    }

    return NULL;
}


char *pop_memory_access_segments(char *mnemonic_arg1, char *mnemonic_arg2, char const *file_name) {

    init_assembly_string(mnemonic_arg1, mnemonic_arg2);

    //Pointer_Segment
    if (strstr(mnemonic_arg1, "pointer")) {
        pop_pointer_segment(mnemonic_arg2);
        return assembly_code;
    }

        //Static_Segment
    else if (strstr(mnemonic_arg1, "static")) {
        pop_static_segment(file_name, mnemonic_arg2);
        return assembly_code;
    }

        //Temp_Segment
    else if (strstr(mnemonic_arg1, "temp")) {
        pop_temp_segment();
        return assembly_code;
    }

        //Segment_pointers: LCL, ARG, THIS, THAT
    else if (((segment_type = strstr(mnemonic_arg1, "local")) ||
              (segment_type = strstr(mnemonic_arg1, "argument")) ||
              (segment_type = strstr(mnemonic_arg1, "this")) || (segment_type = strstr(mnemonic_arg1, "that"))
              || (segment_type = strstr(mnemonic_arg1, "temp")))) {
        substitute(&segment_type);
        pop_segment_pointers(segment_type);
        return assembly_code;
    }
    return NULL;
}


/* Temp_Segment operates between the addresses 5 and 12, so we always start counting from 5
 addr = 5 + i
 SP--
 *addr = *SP
 */
void push_temp_segment() {

    char *assembly_temp = "D=A\n"
                          "@R5\n"
                          "A=D+A\n"
                          "D=M\n"
                          "@SP\n"
                          "A=M\n"
                          "M=D\n"
                          "@SP\n"
                          "M=M+1\n";
    strcat(assembly_code, assembly_temp);

    *(assembly_code + strlen(assembly_code)) = '\0';
}

/* It is stored in a global space between 16 and 255. Variable name in assembler that stores the static var should be
 fileName.i = i
  */
void push_static_segment(char *file_name, char *mnemonic_arg2) {

    char *temp_fileName = strrchr(file_name, '\\');
    char *base_fileName = (char *) calloc(strlen(temp_fileName), sizeof(*base_fileName));
    get_basename_of_theFile(temp_fileName, base_fileName);

    //Initiate assembly code
    *assembly_code = '@';
    strcat(assembly_code, mnemonic_arg2);

    char *assembly_static_p1 = "D=A\n"
                               "@";
    strcat(assembly_code, assembly_static_p1);
    strcat(assembly_code, base_fileName);
    strcat(assembly_code, mnemonic_arg2);

    char *assembly_static_p2 = "M=D\n";
    strcat(assembly_code, assembly_static_p2);

    *(assembly_code + strlen(assembly_code)) = '\0';
    free(base_fileName);
    base_fileName = NULL;
}


/* A fixed 2-place segment. When instruction is "push/pop pointer 0" then use THIS and when 1 use THAT
  *SP = THIS|THAT
  SP++
*/
void push_pointer_segment(char *mnemonic_arg2) {
    // 0 = THIS
    if (*mnemonic_arg2 == '0') {
        char *assembly_pointer = "@THIS\n"
                                 "D=M\n"
                                 "@SP\n"
                                 "A=M\n"
                                 "M=D\n"
                                 "@SP\n"
                                 "M=M+1\n";
        strcat(assembly_code, assembly_pointer);

        // 1 = THAT
    } else if (*mnemonic_arg2 == '1') {
        char *assembly_pointer = "@THAT\n"
                                 "D=M\n"
                                 "@SP\n"
                                 "A=M\n"
                                 "M=D\n"
                                 "@SP\n"
                                 "M=M+1\n";
        strcat(assembly_code, assembly_pointer);
    }

    *(assembly_code + strlen(assembly_code)) = '\0';
}


/*
  *SP = i
  SP++
*/
void push_constant_segment(void) {

    char *assembly_constant = "D=A\n"
                              "@SP\n"
                              "A=M\n"
                              "M=D\n"
                              "@SP\n"
                              "M=M+1\n";
    strcat(assembly_code, assembly_constant);
    *(assembly_code + strlen(assembly_code)) = '\0';
}

/*
  addr = segmentPoint+i (i = mnemonic_arg2)
  *SP=*addr
  SP++
*/
void push_segment_pointers(char *segment_type) {

    char *assembly_segment_pointers_p1 = "D=A\n@";
    strcat(assembly_code, assembly_segment_pointers_p1);
    strcat(assembly_code, segment_type);

    char *assembly_segment_pointers_p2 = "\nA=D+M\n"
                                         "D=M\n"
                                         "@SP\n"
                                         "A=M\n"
                                         "M=D\n"
                                         "@SP\n"
                                         "M=M+1\n";
    strcat(assembly_code, assembly_segment_pointers_p2);
    *(assembly_code + strlen(assembly_code)) = '\0';
}


//==================================================POP======================================================

/* Temp_Segment operates between the addresses 5 and 12, so we always start counting from 5
 addr = 5 + i
 SP--
 *addr = *SP
 */
void pop_temp_segment(void) {

    char *assembly_temp = "D=A\n"
                          "@R5\n"
                          "A=D+A\n"
                          "D=A\n"
                          "@addr\n"
                          "M=D\n"
                          "@SP\n"
                          "M=M-1\n"
                          "@SP\n"
                          "A=M\n"
                          "D=M\n"
                          "@addr\n"
                          "A=M\n"
                          "M=D\n";

    strcat(assembly_code, assembly_temp);
    *(assembly_code + strlen(assembly_code)) = '\0';
}

void pop_static_segment(char *file_name, char *mnemonic_arg2) {

    char *temp_fileName = strrchr(file_name, '\\');
    char *base_fileName = (char *) calloc(strlen(temp_fileName), sizeof(*base_fileName));
    get_basename_of_theFile(temp_fileName, base_fileName);

    char *assembly_static_p1 = "@0\n"
                               "D=A\n"
                               "@";

    strcat(assembly_code, assembly_static_p1);
    strcat(assembly_code, base_fileName);
    strcat(assembly_code, mnemonic_arg2);

    char *assembly_static_p2 = "M=D\n";
    strcat(assembly_code, assembly_static_p2);

    *(assembly_code + strlen(assembly_code)) = '\0';
    free(base_fileName);
    base_fileName = NULL;
}


/*
  addr = segmentPoint+i (i = mnemonic_arg2)
  SP--
  *addr = *SP
*/
void pop_segment_pointers(char *segment_type) {

    char *assembly_segments_p1 = "D=A\n@";
    strcat(assembly_code, assembly_segments_p1);
    strcat(assembly_code, segment_type);

    char *assembly_segments_p2 = "\nA=D+M\n"
                                 "D=A\n"
                                 "@addr\n"
                                 "M=D\n"
                                 "@SP\n"
                                 "M=M-1\n"
                                 "@SP\n"
                                 "A=M\n"
                                 "D=M\n"
                                 "@addr\n"
                                 "A=M\n"
                                 "M=D\n";
    strcat(assembly_code, assembly_segments_p2);
    *(assembly_code + strlen(assembly_code)) = '\0';

}


/*
  SP--
  THIS|THAT = *SP
*/
void pop_pointer_segment(char *mnemonic_arg2) {

    //0 = THIS
    if (*mnemonic_arg2 == '0') {
        char *assembly_pointer = "@SP\n"
                                 "M=M-1\n"
                                 "@SP\n"
                                 "A=M\n"
                                 "D=A\n"
                                 "@THIS\n"
                                 "M=D\n";
        strcat(assembly_code, assembly_pointer);

        // 1 = THAT
    } else if (*mnemonic_arg2 == '1') {
        char *assembly_pointer = "@SP\n"
                                 "M=M-1\n"
                                 "@SP\n"
                                 "A=M\n"
                                 "D=A\n"
                                 "@THAT\n"
                                 "M=D\n";
        strcat(assembly_code, assembly_pointer);
    }

    *(assembly_code + strlen(assembly_code)) = '\0';

}
