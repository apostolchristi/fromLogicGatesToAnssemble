//
// Created by Toor on 2/2/2022.
//

#include "Arithmetic_Logical_Commands.h"

#define C_LENGTH 100 //MAXIMUM possible length of the string


char *arithmetic_assembly_code = NULL;
static int count = 1;


char *arithmetic_segments(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name) {

    arithmetic_assembly_code = calloc(C_LENGTH, sizeof(*arithmetic_assembly_code));

    // Addition
    if (strstr(mnemonic_arg1, "add")) {
        add();
    }
        // Subtraction
    else if (strstr(mnemonic_arg1, "sub")) {
        sub();
    }
        //Negation
    else if (strstr(mnemonic_arg1, "neg")) {
        neg();
    }
        //Equality
    else if (strstr(mnemonic_arg1, "eq")) {
        eq();
    }
        //Greater
    else if (strstr(mnemonic_arg1, "gt")) {
        gt();
    }
        //Less
    else if (strstr(mnemonic_arg1, "lt")) {
        lt();
    }
        //And
    else if (strstr(mnemonic_arg1, "and")) {
        and();
    }
        //Or
    else if (strstr(mnemonic_arg1, "or")) {
        or();
    }
        //Not
    else if (strstr(mnemonic_arg1, "not")) {
        not();
    }


    return arithmetic_assembly_code;
}

/* Integer addition: x+y
 @SP--
 x = x+y
 */
void add() {

    char *assembly_add = "@SP\n"
                         "AM=M-1\n"
                         "D=M\n"
                         "M=0\n"
                         "A=A-1\n"
                         "M=D+M\n";

    strcat(arithmetic_assembly_code, assembly_add);
}

/* Integer subtraction: x-y
 @SP--
 x = x-y
 */
void sub() {

    char *assembly_sub = "@SP\n"
                         "AM=M-1\n"
                         "D=M\n"
                         "M=0\n"
                         "A=A-1\n"
                         "M=M-D\n";

    strcat(arithmetic_assembly_code, assembly_sub);
}

/* Arithmetic negation: -y
 @SP--
 y = -y
 @SP++
 */
void neg() {
    char *assembly_neg = "@SP\n"
                         "AM=M-1\n"
                         "D=!M\n"
                         "D=D+1\n"
                         "M=D\n"
                         "@SP\n"
                         "M=M+1\n";

    strcat(arithmetic_assembly_code, assembly_neg);
}

/* Equality: true if x == y, else false */
void eq() {
    static int count = 1;

    char *str_count = decimal_to_string(&count);

    char *assembly_eq_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "M=0\n"
                           "A=A-1\n"
                           "D=M-D\n"
                           "@if_eq_true_";
    strcat(arithmetic_assembly_code, assembly_eq_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_eq_p2 = "\nD;JEQ\n"
                           "D=0\n"
                           "@if_eq_false_";
    strcat(arithmetic_assembly_code, assembly_eq_p2);
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, "\n0;JMP\n");
    strcat(arithmetic_assembly_code, "(if_eq_true_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "D=-1\n"
                                     "(if_eq_false_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "@SP\n"
                                     "A=M-1\n"
                                     "M=D\n");
    count++;
}

/* Greater than: true if x > y, else false */
void gt() {
    static int count = 1;

    char *str_count = decimal_to_string(&count);

    char *assembly_eq_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "M=0\n"
                           "A=A-1\n"
                           "D=M-D\n"
                           "@if_gt_true_";
    strcat(arithmetic_assembly_code, assembly_eq_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_eq_p2 = "\nD;JGT\n"
                           "D=0\n"
                           "@if_gt_false_";
    strcat(arithmetic_assembly_code, assembly_eq_p2);
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, "\n0;JMP\n");
    strcat(arithmetic_assembly_code, "(if_gt_true_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "D=-1\n"
                                     "(if_gt_false_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "@SP\n"
                                     "A=M-1\n"
                                     "M=D\n");
    count++;
}

/* Less than: true if x < y, else false */
void lt() {

    static int count = 1;

    char *str_count = decimal_to_string(&count);

    char *assembly_eq_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "M=0\n"
                           "A=A-1\n"
                           "D=M-D\n"
                           "@if_lt_true";
    strcat(arithmetic_assembly_code, assembly_eq_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_eq_p2 = "\nD;JLT\n"
                           "D=0\n"
                           "@if_lt_false_";
    strcat(arithmetic_assembly_code, assembly_eq_p2);
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, "\n0;JMP\n");
    strcat(arithmetic_assembly_code, "(if_lt_true");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "D=-1\n"
                                     "(if_lt_false_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "@SP\n"
                                     "A=M-1\n"
                                     "M=D\n");
    count++;

}

/* Bit-wise: x And y */
void and() {
    eq();
}

void or() {

    static int count = 1;

    char *str_count = decimal_to_string(&count);

    char *assembly_eq_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "M=0\n"
                           "A=A-1\n"
                           "D=D|M\n"
                           "@if_or_true";
    strcat(arithmetic_assembly_code, assembly_eq_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_eq_p2 = "\nD;JNE\n"
                           "D=0\n"
                           "@if_or_false_";
    strcat(arithmetic_assembly_code, assembly_eq_p2);
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, "\n0;JMP\n");
    strcat(arithmetic_assembly_code, "(if_or_true");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "D=-1\n"
                                     "(if_or_false_");
    strcat(arithmetic_assembly_code, str_count);
    strcat(arithmetic_assembly_code, ")\n"
                                     "@SP\n"
                                     "A=M-1\n"
                                     "M=D\n");
    count++;
}

//TODO: make sure the impl of this method is correct (on assembly level).
/* Bit-wise: Not y */
void not() {

    char *assembly_not = "@SP\n"
                         "AM=M-1\n"
                         "D=!M\n"
                         "M=D\n"
                         "@SP\n"
                         "M=M+1";
    strcat(arithmetic_assembly_code, assembly_not);

}