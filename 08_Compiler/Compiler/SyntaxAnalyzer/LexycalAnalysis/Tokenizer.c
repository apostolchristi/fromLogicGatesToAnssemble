//
// Created by Toor on 6/1/2022.
//

#include "Tokenizer.h"
// Token - a token is a string of characters that has a meaning

void Tokenizer_destructor() {
    TokensTable_destructor();
}


void Tokenizer_initializer(char *input) {

    FILE *input_file = NULL;
    DIR *input_dir = NULL;
    FILE *output_file = NULL;
    char *file_pathName = NULL;
    struct dirent *dir_file;

    TokensTable_constructor();

    //Reads a File
    if (strstr(input, ".jack") != NULL) {
        input_file = openFile(input, "r");
        file_pathName = setFilePath(input, "w", NULL);
        output_file = openFile(file_pathName, "w");
        hasMoreTokens(input_file, output_file);
    }
    //Reads a Directory
    else if ((input_dir = openDir(input)) != NULL) {
        while ((dir_file = readdir(input_dir)) != NULL) {
            if (strstr(dir_file->d_name, ".jack") != NULL) {
                file_pathName = setFilePath(input, "r", dir_file->d_name);
                input_file = openFile(file_pathName, "r");
                file_pathName = setFilePath(file_pathName, "w", NULL);
                output_file = openFile(file_pathName, "w");
                hasMoreTokens(input_file, output_file);
            }
        }
    }
    fclose(input_file);input_file = NULL;
    free(file_pathName);file_pathName = NULL;
    closedir(input_dir);input_dir = NULL;

    Tokenizer_destructor();
}


bool hasMoreTokens(FILE *input_file, FILE *output_file) {

    char input_file_line[INPUT_LENGTH];
    //Opening Tag
    fputs("<tokens>\n", output_file);

    while ((fgets(input_file_line, INPUT_LENGTH, input_file) != NULL) == true) {
        Tokenizer_advance(input_file_line, output_file);
    }

    //Closing Tag
    fputs("</tokens>\n", output_file);
    return false;
}


char *Tokenizer_advance(char *input_file_line, FILE *output_file) {

    char *token_type = NULL, *output_line = NULL, *token = NULL;
    int *index = calloc(1, sizeof(int));

    while ((token = token_parser(input_file_line, index)) != NULL) {
        token_type = tokenType(token);
        output_line = xmlLineBuilder(token, token_type);
        fputs(output_line, output_file);
        free(token); free(output_line);
    }
    free(index);
    return NULL;
}


char *tokenType(char *token) {

    if (isDigit(token) == true && isDecimalRange(token)) {
        return "intConst";

    } else if (isKeyword(token) == true) {
        return "keyword";

    } else if (strlen(token) == 1 && isSymbol(token)) {
        return "symbol";

    } else if (isStringConstant(token))
        return "stringConst";

    else if (isFirstCharDigit(token) == false) {
        return "identifier";
    }
    return NULL;
}
