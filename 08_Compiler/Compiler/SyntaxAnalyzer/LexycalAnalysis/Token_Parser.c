//
// Created by Toor on 6/12/2022.
//

#include "Token_Parser.h"

char *token_parser(char *input_file_line, int *index) {

    char tempToken[strlen(input_file_line)];
    char *token = NULL;
    char *currentSymbol = calloc(2, sizeof(*currentSymbol));
    char *nextSymbol = calloc(2, sizeof(*nextSymbol));

    //For readability
    *currentSymbol = input_file_line[*index];
    *nextSymbol = input_file_line[*index+1];

    //if any comments at the beginning or empty line THEN exit;
    if ((*currentSymbol == '/' && *nextSymbol == '/') || *currentSymbol == '\r' || *currentSymbol == '\n') {
        return NULL;
    }

    for (int i = 0; *currentSymbol != '\0'; *index = *index + 1) {
        *currentSymbol = input_file_line[*index];
        *nextSymbol = input_file_line[*index+1];

        // if tabs or space then skip one round
        if (*currentSymbol == '\t' || *currentSymbol == ' ') {
            continue;
        //if any comments, newline or ... then exit.
        } else if ( (*currentSymbol == '/' &&  *nextSymbol == '/')
        || *currentSymbol == '\n' || *currentSymbol == '\r' ) {
            return NULL;
        }

        tempToken[i++] = *currentSymbol;

        if (isSymbol(currentSymbol) == true ||isSymbol(nextSymbol) == true ||
        *nextSymbol == ' ' || *nextSymbol == '\"') {
            //Only for String constants
            if(tempToken[0] == '\"' && *nextSymbol == '\"') {
                tempToken[i++] = '\"';
            }

            tempToken[i] = '\0';
            token = (char *) malloc(strlen(tempToken) * sizeof(*token));
            *index = *index + 1;
            free(currentSymbol); free(nextSymbol);
            return token = strdup(tempToken);
        }
    }
    return NULL;
}


char *xmlLineBuilder(char *token, char *token_type) {

    char *line = (char *) calloc(TOKEN_LENGTH, sizeof(*line));
    *line = '<';
    strcat(line, token_type);
    strcat(line, "> ");
    strcat(line, token);
    strcat(line, " </");
    strcat(line, token_type);
    strcat(line, ">\n\0");
    return line;
}


char *setFilePath(char *path, char *type, char *dir_file_name) {

    char *file_name = NULL;
    file_name = (char *) calloc(200, sizeof(*file_name));

    //For Directory
    if (*type == 'r') {
        strcat(file_name, path);
        strcat(file_name, "\\");
        strcat(file_name, dir_file_name);
        return file_name;
    }
    //For "out" file. Adding it to the same folder with the same name, but .xml ending
    else if (*type == 'w') {
        size_t length = strlen(path) - 1;
        char *t = "\0lmx";
        file_name = strdup(path);
        for (int i = length, j = 0; file_name[i] != '.'; --i, j++) {
            file_name[i] = t[j];
        }
        return file_name;
    }
    return NULL;
}


FILE *openFile(char *input, char *type) {

    FILE *input_file = NULL;

    input_file = fopen(input, type);

    // Check file
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open current file %s\n", input);
        exit(1);
    }

    return input_file;
}

DIR *openDir(char *input) {

    DIR *input_dir = NULL;
    input_dir = opendir(input);

    // Check Dir
    if (input_dir == NULL) {
        fprintf(stderr, "Failed to open current directory %s\n", input);
        exit(1);
    }
    return input_dir;
}