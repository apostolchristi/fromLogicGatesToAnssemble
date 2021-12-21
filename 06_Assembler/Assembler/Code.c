//
// Created by Toor on 11/25/2021.
//

#include "Code.h"

#define A_POSITION 3
#define COMP_POSITION 4
#define DEST_POSITION 10
#define JMP_POSITION 13

#define HT_SIZE_OF_10 10
#define HT_SIZE_OF_30 30

destjump_bits arr000 = {0, 0, 0};
destjump_bits arr001 = {0, 0, 1};
destjump_bits arr010 = {0, 1, 0};
destjump_bits arr011 = {0, 1, 1};
destjump_bits arr100 = {1, 0, 0};
destjump_bits arr101 = {1, 0, 1};
destjump_bits arr110 = {1, 1, 0};
destjump_bits arr111 = {1, 1, 1};

comp_bits zero = {1, 0, 1, 0, 1, 0, 0};
comp_bits one1 = {1, 1, 1, 1, 1, 1, 0};
comp_bits neg1 = {1, 1, 1, 0, 1, 0, 0};
comp_bits D = {0, 0, 1, 1, 0, 0, 0};
comp_bits A = {1, 1, 0, 0, 0, 0, 0};
comp_bits notD = {0, 0, 1, 1, 0, 1, 0};
comp_bits notA = {1, 1, 0, 0, 0, 1, 0};
comp_bits negD = {0, 0, 1, 1, 1, 1, 0};
comp_bits negA = {1, 1, 0, 0, 1, 1, 0};
comp_bits Dplus1 = {0, 1, 1, 1, 1, 1, 0};
comp_bits Aplus1 = {1, 1, 0, 1, 1, 1, 0};
comp_bits Dminus1 = {0, 0, 1, 1, 1, 0, 0};
comp_bits Aminus1 = {1, 1, 0, 0, 1, 0, 0};
comp_bits DplusA = {0, 0, 0, 0, 1, 0, 0};
comp_bits DminusA = {0, 1, 0, 0, 1, 1, 0};
comp_bits AminusD = {0, 0, 0, 1, 1, 1, 0};
comp_bits DandA = {0, 0, 0, 0, 0, 0, 0};
comp_bits DorA = {0, 1, 0, 1, 0, 1, 0};

comp_bits notM = {1, 1, 0, 0, 0, 1, 1};
comp_bits M = {1, 1, 0, 0, 0, 0, 1};
comp_bits minusM = {1, 1, 0, 0, 1, 1, 1};
comp_bits Mplus1 = {1, 1, 0, 1, 1, 1, 1};
comp_bits Mminus1 = {1, 1, 0, 0, 1, 0, 1};
comp_bits DplusM = {0, 0, 0, 0, 1, 0, 1};
comp_bits DminusM = {0, 1, 0, 0, 1, 1, 1};
comp_bits MminusD = {0, 0, 0, 1, 1, 1, 1};
comp_bits DandM = {0, 0, 0, 0, 0, 0, 1};
comp_bits DorM = {0, 1, 0, 1, 0, 1, 1};


static HashTable *jump_table;
static HashTable *dest_table;
static HashTable *comp_table;


void destructor_Code() {

    if(jump_table != NULL) {
        ht_free(jump_table);
        jump_table = NULL;
    }

    if(dest_table != NULL) {
        ht_free(dest_table);
        dest_table = NULL;
    }

    if (comp_table != NULL) {
        ht_free(comp_table);
        comp_table = NULL;
    }


}

void jmp_instructions(short *binary_instruction, char *key) {

    //Initialize if needed
    if (jump_table == NULL)
        jump_table = initialize_jump_instructions();

    HashTableItem *jump_item = ht_search(jump_table, key);

    //Additional check for safety
    if (jump_item == NULL) {
        fprintf(stderr, "There is no such c-type instruction: \"%s\"", key);
        exit(0);
    }

    destjump_bits *jump_bits = jump_item->value;

    //Bits are set into the right position into the binary_instruction
    for (short j = 0; j < DESTJUMP_ARRAY_LENGTH; ++j)
        binary_instruction[j + JMP_POSITION] = jump_bits->instructions[j];

}


void dest_instructions(short *binary_instruction, char *key) {

    //Initialize if needed
    if (dest_table == NULL)
        dest_table = initialize_dest_instructions();

    HashTableItem *dest_item = ht_search(dest_table, key);

    //Additional check for safety
    if (dest_item == NULL) {
        fprintf(stderr, "There is no such c-type instruction: %s", key);
        exit(0);
    }

    destjump_bits *dest_bits = dest_item->value;

    //Bits are set into the right position into the binary_instruction
    for (int j = 0; j < DESTJUMP_ARRAY_LENGTH; ++j)
        binary_instruction[j + DEST_POSITION] = dest_bits->instructions[j];

}


void comp_instructions(short *binary_instruction, char *key) {

    //Initialize if needed
    if (comp_table == NULL)
        comp_table = initialize_comp_instructions();

    HashTableItem *comp_item = ht_search(comp_table, key);

    //Additional check for safety
    if (comp_item == NULL) {
        fprintf(stderr, "There is no such c-type instruction: %s", key);
        exit(0);
    }

    comp_bits *comp_bits = comp_item->value;

    //Bits are set into the right position into the binary_instruction
    binary_instruction[A_POSITION] = comp_bits->a;
    for (int j = 0; j < COMP_ARRAY_LENGTH; ++j)
        binary_instruction[j + COMP_POSITION] = comp_bits->instructions[j];
}


HashTable *initialize_jump_instructions() {

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

HashTable *initialize_dest_instructions() {

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

HashTable *initialize_comp_instructions() {
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