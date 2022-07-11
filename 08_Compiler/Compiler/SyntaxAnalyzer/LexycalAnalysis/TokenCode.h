//
// Created by Toor on 6/12/2022.
//

#ifndef COMPILER_TOKENCODE_H
#define COMPILER_TOKENCODE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "../../DataStructure/List.h"
#include "../../DataStructure/LinkedList.h"

#define INPUT_LENGTH 127    //maximum allowed length of the input file line
#define TOKEN_LENGTH 60 //MAXIMUM possible length of the string


void TokenCode_constructor();
void TokenCode_destructor();

List *getKeywordsList();
List *getSymbolsList();
LinkedList getTokenList();
char *getNextToken();

bool isKeyword(char *keyword);
bool isSymbol(char *symbol);
bool isFirstCharDigit(char *token);
bool isDecimalRange(char *value);
bool isStringConstant(char *str);
bool isDigit(char const *value);
int string_to_decimal(const char *string);
char *decimal_to_string(int *decimal);

char *token_parser(char *input_file_line, int *index);
char *terminalTagBuilder(char *token, char *token_type);

/* second argument @dir_file_name is only for Directory, let it be NULL if it's a file*/
char *setFilePath(char const *path, char const *type, char *dir_file_name);
FILE *openFile(char const *input , char *type);
DIR *openDir(char const *input);

#endif //COMPILER_TOKENCODE_H
