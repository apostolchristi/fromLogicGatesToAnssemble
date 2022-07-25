//
// Created by Toor on 6/1/2022.
//

#include "Tokenizer.h"
// Token - a token is a string of characters that has a meaning


char input_file_line[INPUT_LENGTH];


void Tokenizer_initializer(char const *input) {

    FILE *input_file = NULL;
    DIR *input_dir = NULL;
    char *file_pathName = NULL;
    struct dirent *dir_file;


    //Reads a File
    if (strstr(input, ".jack") != NULL) {
        TokenCode_constructor();
        input_file = openFile(input, "r");
        file_pathName = setFilePath(input, "w", NULL);

        while (hasMoreTokens(input_file)) {
            Tokenizer_advance();
        }

        CompilationEngine_constructor(file_pathName);
    }
        //Reads a Directory
    else if ((input_dir = openDir(input)) != NULL) {
        while ((dir_file = readdir(input_dir)) != NULL) {
            if (strstr(dir_file->d_name, ".jack") != NULL) {
                TokenCode_constructor();
                file_pathName = setFilePath(input, "r", dir_file->d_name);
                input_file = openFile(file_pathName, "r");
                file_pathName = setFilePath(file_pathName, "w", NULL);

                while (hasMoreTokens(input_file)) {
                    Tokenizer_advance();
                }
                CompilationEngine_constructor(file_pathName);

                TokenCode_destructor();
            }
        }
    }

    fclose(input_file);
    free(file_pathName);
    closedir(input_dir);

    TokenCode_destructor();

}

bool hasMoreTokens(FILE *input_file) {

   if ((fgets(input_file_line, INPUT_LENGTH, input_file) != NULL) == true) {
       return true;
   }
    return false;
}


void Tokenizer_advance() {
    char *token = NULL;
    int *index = calloc(1, sizeof(int));
    LinkedList token_list = getTokenList();

    while ((token = token_parser(input_file_line, index)) != NULL) {
        insert_AtEndOf_LinkedList(&token_list, token);
    }

    free(token);
    free(index);
}


char *tokenType(char *token) {

    if (isKeyword(token) == true) {
        return "keyword";
    } else if (strlen(token) == 1 && isSymbol(token)) {
        symbol(token);
        return "symbol";
    } else if (isFirstCharDigit(token) == false) {
        return "identifier";
    } else if (isDigit(token) == true && isDecimalRange(token)) {
        return "intConst";
    } else if (isStringConstant(token)) {
        return "stringConst";
    }
    return NULL;
}

