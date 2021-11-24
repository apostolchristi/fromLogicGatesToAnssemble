
//
// Created by Toor on 9/30/2021.
//

#include "SymbolTable.h"

#define A_POSITION 3
#define COMP_POSITION 4
#define DEST_POSITION 10
#define JMP_POSITION 13
#define HT_SIZE_OF_10 10
#define HT_SIZE_OF_30 30
#define HT_SIZE_OF_500 500

destjump_bits arr000 = {0, 0, 0, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr001 = {0, 0, 1, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr010 = {0, 1, 0, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr011 = {0, 1, 1, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr100 = {1, 0, 0, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr101 = {1, 0, 1, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr110 = {1, 1, 0, DESTJUMP_ARRAY_LENGTH};
destjump_bits arr111 = {1, 1, 1, DESTJUMP_ARRAY_LENGTH};


comp_bits zero = {1, 0, 1, 0, 1, 0, 0, COMP_ARRAY_LENGTH};
comp_bits one1 = {1, 1, 1, 1, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits neg1 = {1, 1, 1, 0, 1, 0, 0, COMP_ARRAY_LENGTH};
comp_bits D = {0, 0, 1, 1, 0, 0, 0, COMP_ARRAY_LENGTH};
comp_bits A = {1, 1, 0, 0, 0, 0, 0, COMP_ARRAY_LENGTH};
comp_bits notD = {0, 0, 1, 1, 0, 1, 0, COMP_ARRAY_LENGTH};
comp_bits notA = {1, 1, 0, 0, 0, 1, 0, COMP_ARRAY_LENGTH};
comp_bits negD = {0, 0, 1, 1, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits negA = {1, 1, 0, 0, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits Dplus1 = {0, 1, 1, 1, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits Aplus1 = {1, 1, 0, 1, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits Dminus1 = {0, 0, 1, 1, 1, 0, 0, COMP_ARRAY_LENGTH};
comp_bits Aminus1 = {1, 1, 0, 0, 1, 0, 0, COMP_ARRAY_LENGTH};
comp_bits DplusA = {0, 0, 0, 0, 1, 0, 0, COMP_ARRAY_LENGTH};
comp_bits DminusA = {0, 1, 0, 0, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits AminusD = {0, 0, 0, 1, 1, 1, 0, COMP_ARRAY_LENGTH};
comp_bits DandA = {0, 0, 0, 0, 0, 0, 0, COMP_ARRAY_LENGTH};
comp_bits DorA = {0, 1, 0, 1, 0, 1, 0, COMP_ARRAY_LENGTH};

comp_bits notM = {1, 1, 0, 0, 0, 1, 1, COMP_ARRAY_LENGTH};
comp_bits M = {1, 1, 0, 0, 0, 0, 1, COMP_ARRAY_LENGTH};
comp_bits minusM = {1, 1, 0, 0, 1, 1, 1, COMP_ARRAY_LENGTH};
comp_bits Mplus1 = {1, 1, 0, 1, 1, 1, 1, COMP_ARRAY_LENGTH};
comp_bits Mminus1 = {1, 1, 0, 0, 1, 0, 1, COMP_ARRAY_LENGTH};
comp_bits DplusM = {0, 0, 0, 0, 1, 0, 1, COMP_ARRAY_LENGTH};
comp_bits DminusM = {0, 1, 0, 0, 1, 1, 1, COMP_ARRAY_LENGTH};
comp_bits MminusD = {0, 0, 0, 1, 1, 1, 1, COMP_ARRAY_LENGTH};
comp_bits DandM = {0, 0, 0, 0, 0, 0, 1, COMP_ARRAY_LENGTH};
comp_bits DorM = {0, 1, 0, 1, 0, 1, 1, COMP_ARRAY_LENGTH};

short R0_or_SP[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
short R1_or_LCL[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
short R2_or_ARG[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0};
short R3_or_THIS[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1};
short R4_or_THAT[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0};
short R5[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1};
short R6[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0};
short R7[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
short R8[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0};
short R9[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1};
short R10[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0};
short R11[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1};
short R12[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};
short R13[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1};
short R14[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0};
short R15[BITS_16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1};
short SCREEN[BITS_16] = {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
short KBD[BITS_16] = {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


HashTable *jump_instructions() {

    HashTable *ht_jump = ht_create(HT_SIZE_OF_10);

    ht_insert(ht_jump, "", &arr000);
    ht_insert(ht_jump, "JGT", &arr001);
    ht_insert(ht_jump, "JEQ", &arr010);
    ht_insert(ht_jump, "JGE", &arr011);
    ht_insert(ht_jump, "JLT", &arr100);
    ht_insert(ht_jump, "JNE", &arr101);
    ht_insert(ht_jump, "JLE", &arr110);
    ht_insert(ht_jump, "JMP", &arr111);

    return ht_jump;
}

void jmp_parse(HashTableItem *item, short *binary_instruction) {
    destjump_bits *jump_bits = item->value;

    for (int j = 0; j < jump_bits->arrayLength; ++j) {
        binary_instruction[j + JMP_POSITION] = jump_bits->destjump[j];
    }
}

HashTable *dest_instructions() {

    HashTable *ht_jump = ht_create(HT_SIZE_OF_10);

    ht_insert(ht_jump, "", &arr000);
    ht_insert(ht_jump, "M", &arr001);
    ht_insert(ht_jump, "D", &arr010);
    ht_insert(ht_jump, "MD", &arr011);
    ht_insert(ht_jump, "A", &arr100);
    ht_insert(ht_jump, "AM", &arr101);
    ht_insert(ht_jump, "AD", &arr110);
    ht_insert(ht_jump, "AMD", &arr111);

    return ht_jump;

}

void dest_parse(HashTableItem *item, short *binary_instruction) {
    destjump_bits *dest_bits = item->value;
    for (int j = 0; j < dest_bits->arrayLength; ++j) {
        binary_instruction[j + DEST_POSITION] = dest_bits->destjump[j];
    }
}

HashTable *comp_instructions() {
    HashTable *ht_comp = ht_create(HT_SIZE_OF_30);

    ht_insert(ht_comp, "0", &zero);
    ht_insert(ht_comp, "1", &one1);
    ht_insert(ht_comp, "-1", &neg1);
    ht_insert(ht_comp, "D", &D);
    ht_insert(ht_comp, "A", &A);
    ht_insert(ht_comp, "!D", &notD);
    ht_insert(ht_comp, "!A", &notA);
    ht_insert(ht_comp, "-D", &negD);
    ht_insert(ht_comp, "-A", &negA);
    ht_insert(ht_comp, "D+1", &Dplus1);
    ht_insert(ht_comp, "A+1", &Aplus1);
    ht_insert(ht_comp, "D-1", &Dminus1);
    ht_insert(ht_comp, "A-1", &Aminus1);
    ht_insert(ht_comp, "D+A", &DplusA);
    ht_insert(ht_comp, "D-A", &DminusA);
    ht_insert(ht_comp, "A-D", &AminusD);
    ht_insert(ht_comp, "D&A", &DandA);
    ht_insert(ht_comp, "D|A", &DorA);

    ht_insert(ht_comp, "M", &M);
    ht_insert(ht_comp, "!M", &notM);
    ht_insert(ht_comp, "-M", &minusM);
    ht_insert(ht_comp, "M+1", &Mplus1);
    ht_insert(ht_comp, "M-1", &Mminus1);
    ht_insert(ht_comp, "D+M", &DplusM);
    ht_insert(ht_comp, "D-M", &DminusM);
    ht_insert(ht_comp, "M-D", &MminusD);
    ht_insert(ht_comp, "D&M", &DandM);
    ht_insert(ht_comp, "D|M", &DorM);

    return ht_comp;
}

void comp_parse(HashTableItem *item, short *binary_instruction) {
    comp_bits *comp_bits = item->value;
    binary_instruction[A_POSITION] = comp_bits->a;
    for (int j = 0; j < comp_bits->arrayLength; ++j) {
        binary_instruction[j + COMP_POSITION] = comp_bits->comp[j];
    }
}

/* Represents memory locations where the programmer wants to maintain values*/
HashTable *variable_symbols() {

    HashTable *ht = ht_create(HT_SIZE_OF_10);

    return ht;
}

/* Represents destinations of goto instructions*/
HashTable *label_symbols() {

    return ht_create(HT_SIZE_OF_10);

}

/* Represents special memory locations */
HashTable *pre_defined_symbols() {
    HashTable *ht = ht_create(HT_SIZE_OF_30);

    ht_insert(ht, "R0",&R0_or_SP);
    ht_insert(ht, "R1",&R1_or_LCL);
    ht_insert(ht, "R2",&R2_or_ARG);
    ht_insert(ht, "R3",&R3_or_THIS);
    ht_insert(ht, "R4",&R4_or_THAT);
    ht_insert(ht, "R5",&R5);
    ht_insert(ht, "R6",&R6);
    ht_insert(ht, "R7",&R7);
    ht_insert(ht, "R8",&R8);
    ht_insert(ht, "R9",&R9);
    ht_insert(ht, "R10",&R10);
    ht_insert(ht, "R11",&R11);
    ht_insert(ht, "R12",&R12);
    ht_insert(ht, "R13",&R13);
    ht_insert(ht, "R14",&R14);
    ht_insert(ht, "R15",&R15);
    ht_insert(ht, "SCREEN",&SCREEN);
    ht_insert(ht, "KBD",&KBD);

    ht_insert(ht, "SP", &R0_or_SP);
    ht_insert(ht, "LCL",R1_or_LCL);
    ht_insert(ht, "ARG",R2_or_ARG);
    ht_insert(ht, "THIS",R3_or_THIS);
    ht_insert(ht, "THAT",R4_or_THAT);


    return ht;

}
