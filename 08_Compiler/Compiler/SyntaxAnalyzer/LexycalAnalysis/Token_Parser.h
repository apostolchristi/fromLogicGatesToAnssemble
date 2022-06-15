//
// Created by Toor on 6/12/2022.
//

#ifndef COMPILER_TOKEN_PARSER_H
#define COMPILER_TOKEN_PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include "Tokens_Table.h"

#define INPUT_LENGTH 127    //maximum allowed length of the input file line
#define TOKEN_LENGTH 60 //MAXIMUM possible length of the string

char *token_parser(char *input_file_line, int *index);
char *xmlLineBuilder(char *token, char *token_type);

/* second argument @dir_file_name is only for Directory, let it be NULL if it's a file*/
char *setFilePath(char *path, char *type, char *dir_file_name);

FILE *openFile(char *input , char *type);
DIR *openDir(char *input);

#endif //COMPILER_TOKEN_PARSER_H
