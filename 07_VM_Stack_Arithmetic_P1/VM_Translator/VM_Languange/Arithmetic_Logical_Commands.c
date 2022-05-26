//
// Created by Toor on 2/2/2022.
//

#include "Arithmetic_Logical_Commands.h"

#define C_LENGTH 140 //MAXIMUM possible length of the string


char *arithmetic_assembly_code = NULL;

char *arithmetic_segments(char *command) {

    arithmetic_assembly_code = calloc(C_LENGTH, sizeof(*arithmetic_assembly_code));

    // Addition
    if (strstr(command, "add")) {
        add();
    }
        // Subtraction
    else if (strstr(command, "sub")) {
        sub();
    }
        //Negation
    else if (strstr(command, "neg")) {
        neg();
    }
        //Equality
    else if (strstr(command, "eq")) {
        eq();
    }
        //Greater
    else if (strstr(command, "gt")) {
        gt();
    }
        //Less
    else if (strstr(command, "lt")) {
        lt();
    }
        //And
    else if (strstr(command, "and")) {
        and();
    }
        //Or
    else if (strstr(command, "or")) {
        or();
    }
        //Not
    else if (strstr(command, "not")) {
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

    char *assembly_gt_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "A=A-1\n"
                           "D=M-D\n"
                           "@if_gt_true_";
    strcat(arithmetic_assembly_code, assembly_gt_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_gt_p2 = "\nD;JGT\n"
                           "@if_gt_false_";
    strcat(arithmetic_assembly_code, assembly_gt_p2);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_gt_p3 = "\nD=0\n"
                           "0;JMP\n";
    strcat(arithmetic_assembly_code, assembly_gt_p3);
    strcat(arithmetic_assembly_code, "(if_gt_true_");
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_gt_p4 = ")\n"
                           "D=-1\n"
                           "(if_gt_false_";
    strcat(arithmetic_assembly_code, assembly_gt_p4);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_gt_p5 = ")\n"
                           "@SP\n"
                           "A=M-1\n"
                           "M=D\n";
    strcat(arithmetic_assembly_code, assembly_gt_p5);
    count++;
}

/* Less than: true if x < y, else false */
void lt() {
    static int count = 1;

    char *str_count = decimal_to_string(&count);

    char *assembly_lt_p1 = "@SP\n"
                           "AM=M-1\n"
                           "D=M\n"
                           "A=A-1\n"
                           "D=M-D\n"
                           "@if_lt_true_";
    strcat(arithmetic_assembly_code, assembly_lt_p1);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_lt_p2 = "\nD;JLT\n"
                           "@if_lt_false_";
    strcat(arithmetic_assembly_code, assembly_lt_p2);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_lt_p3 = "\nD=0\n"
                           "0;JMP\n";
    strcat(arithmetic_assembly_code, assembly_lt_p3);
    strcat(arithmetic_assembly_code, "(if_lt_true_");
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_lt_p4 = ")\n"
                           "D=-1\n"
                           "(if_lt_false_";
    strcat(arithmetic_assembly_code, assembly_lt_p4);
    strcat(arithmetic_assembly_code, str_count);
    char *assembly_lt_p5 = ")\n"
                           "@SP\n"
                           "A=M-1\n"
                           "M=D\n";
    strcat(arithmetic_assembly_code, assembly_lt_p5);
    count++;

}

/* Bit-wise: x And y */
void and() {
    char *assembly_and = "@SP\n"
                         "AM=M-1\n"
                         "D=M\n"
                         "A=A-1\n"
                         "D=D&M\n"
                         "@SP\n"
                         "A=M-1\n"
                         "M=D\n";
    strcat(arithmetic_assembly_code, assembly_and);
}

/* Bit-wise: x Or y */
void or() {

    char *assembly_or = "@SP\n"
                        "AM=M-1\n"
                        "D=M\n"
                        "A=A-1\n"
                        "D=D|M\n"
                        "@SP\n"
                        "A=M-1\n"
                        "M=D\n";
    strcat(arithmetic_assembly_code, assembly_or);

}

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