//
// Created by Toor on 6/9/2022.
//

#ifndef COMPILER_TOKENS_TABLE_H
#define COMPILER_TOKENS_TABLE_H

#include "../../DataStructure/List.h"
#include "../../HellpingFunctions.h"

void TokensTable_constructor();
void TokensTable_destructor();

List *initialize_keywords();
List *initialize_symbols();

bool isKeyword(char *keyword);
bool isSymbol(char *symbol);
bool isFirstCharDigit(char *token);
bool isDecimalRange(char *value);
bool isStringConstant(char *str);

#endif //COMPILER_TOKENS_TABLE_H
