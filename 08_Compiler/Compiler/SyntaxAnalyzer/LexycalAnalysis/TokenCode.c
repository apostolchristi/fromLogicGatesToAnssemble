//
// Created by Toor on 6/12/2022.
//

#include "TokenCode.h"



#define K_SIZE 21
#define S_SIZE 19

List *keyword_list;
List *symbol_list;
LinkedList token_list;

void TokenCode_constructor() {

    if(keyword_list == NULL) {
        keyword_list = getKeywordsList();
    }

    if(symbol_list == NULL) {
        symbol_list = getSymbolsList();
    }

    if(token_list == NULL) {
        token_list = create_LinkedList();
    }
}



void TokenCode_destructor() {
    if(keyword_list != NULL) {
        list_delete(keyword_list);
        keyword_list = NULL;
    }

    if(symbol_list != NULL) {
        list_delete(symbol_list);
        symbol_list = NULL;
    }

    if(token_list != NULL) {
        delete_LinkedList(&token_list);
        token_list = NULL;
    }
}


char *token_parser(char *input_file_line, int *index) {

    char tempToken[strlen(input_file_line)];
    char *currentSymbol = calloc(2, sizeof(*currentSymbol));
    char *nextSymbol = calloc(2, sizeof(*nextSymbol));

    //For readability
    *currentSymbol = input_file_line[*index];
    *nextSymbol = input_file_line[*index+1];

    //if any comments at the beginning or empty line THEN exit;
    if ((*currentSymbol == '/' && *nextSymbol == '/') || (*currentSymbol == '/' && *nextSymbol == '*') || *currentSymbol == '\r' || *currentSymbol == '\n') {
        return NULL;
    }

    for (int i = 0; *currentSymbol != '\0'; *index = *index + 1) {
        *currentSymbol = input_file_line[*index];
        *nextSymbol = input_file_line[*index+1];

        // if tabs or space then skip one round
        if (*currentSymbol == '\t' || *currentSymbol == ' ') {
            continue;
        }
            //if any comments, newline or ... then exit.
        else if ( (*currentSymbol == '/' &&  *nextSymbol == '/')
                  || *currentSymbol == '\n' || *currentSymbol == '\r' ) {
            return NULL;
        }

        tempToken[i++] = *currentSymbol;

        if (isSymbol(currentSymbol) == true || isSymbol(nextSymbol) == true ||
            *nextSymbol == ' ' || *nextSymbol == '\"') {
            //Only for String constants
            if(tempToken[0] == '\"' && *nextSymbol == '\"') {
                tempToken[i++] = '\"';
            }

            tempToken[i] = '\0';
            *index = *index + 1;
            free(currentSymbol); free(nextSymbol);
            return strdup(tempToken);
        }
    }

    return NULL;
}


bool isKeyword(char *keyword){

    if(list_lookup(keyword_list, keyword) == true) {
        return true;
    }
    return false;
}


bool isSymbol(char *symbol) {
    if(list_lookup(symbol_list, symbol) == true) {
        return true;
    }
    return false;
}


bool isFirstCharDigit(char *token) {

    if(*token >= 48 && *token <= 57 ) {
        return true;
    }
    return false;
}


/* x >= 0 && x <= 32767 */
bool isDecimalRange(char *command) {
    int decimal = string_to_decimal(command);

    if ( decimal >= 0 && decimal <= 32767) {
        return true;
    }

    return false;
}


bool isStringConstant(char *str) {

    size_t length = strlen(str)-1;

    //Removes double quotes ("") from the token to avoid conflicts in xml file.
    if (*str == '"' || *(str+length) == '"') {

        int i;
        for (i = 0; i < length; ++i) {
            str[i] = str[i+1];
        }
        str[i-1] = '\0';
        return true;
    }
    return false;
}


bool isDigit(char const *command) {

    size_t length = strlen(command);
    size_t index = 0;
    while ( (command[index] >= 48 && command[index] <= 57) && (index++ != length)) {
        if (index == length) {
            return true;
        }
    }

    return false;
}

int string_to_decimal(const char *string) {
    const short constant = 1;
    const short asciiZero = 48;
    int temp = 0, decimal = 0;
    int digit_length = (int) strlen(string) - 1;

    for (int decimal_units = 1; digit_length >= 0; decimal_units *= 10, digit_length--) {
        temp = *(string + digit_length);
        temp = (temp - asciiZero) * (constant * decimal_units);
        decimal += temp;
    }

    return decimal;
}


char *decimal_to_string(int *decimal) {

    char *the_string = (char *) calloc(6, sizeof(*the_string));

    sprintf(the_string, "%d", *decimal);

    return the_string;
}


void symbol(char *token) {

    char *new_token = NULL;

    if (*token == '<' || *token == '>' || *token == '\"' || *token == '&') {
        switch (*token) {
            case '<':
                new_token = "&lt";
                break;
            case '>':
                new_token = "&gt";
                break;
            case '\"':
                new_token = "&quot";
                break;
            case '&':
                new_token = "&amp";
                break;
        }
        token = realloc(token, strlen(new_token));
        strcpy(token, new_token);
    }
}

char *terminalTagBuilder(char *token, char *token_type) {

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


char *setFilePath(char const *path, char const *type, char *dir_file_name) {

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


FILE *openFile(char const *input, char *type) {

    FILE *input_file = NULL;

    input_file = fopen(input, type);

    // Check file
    if (input_file == NULL) {
        fprintf(stderr, "Failed to open current file %s\n", input);
        exit(1);
    }

    return input_file;
}


DIR *openDir(char const *input) {

    DIR *input_dir = NULL;
    input_dir = opendir(input);

    // Check Dir
    if (input_dir == NULL) {
        fprintf(stderr, "Failed to open current directory %s\n", input);
        exit(1);
    }
    return input_dir;
}


List *getKeywordsList() {
    List *keyw_list = list_create(K_SIZE);
    list_addItem(keyw_list, "class");
    list_addItem(keyw_list, "constructor");
    list_addItem(keyw_list, "function");
    list_addItem(keyw_list, "method");
    list_addItem(keyw_list, "field");
    list_addItem(keyw_list, "static");
    list_addItem(keyw_list, "var");
    list_addItem(keyw_list, "int");
    list_addItem(keyw_list, "char");
    list_addItem(keyw_list, "boolean");
    list_addItem(keyw_list, "void");
    list_addItem(keyw_list, "true");
    list_addItem(keyw_list, "false");
    list_addItem(keyw_list, "null");
    list_addItem(keyw_list, "this");
    list_addItem(keyw_list, "let");
    list_addItem(keyw_list, "do");
    list_addItem(keyw_list, "if");
    list_addItem(keyw_list, "else");
    list_addItem(keyw_list, "while");
    list_addItem(keyw_list, "return");
    return keyw_list;
}


List *getSymbolsList() {
    List *symb_list = list_create(S_SIZE);
    list_addItem(symb_list, "{");
    list_addItem(symb_list, "}");
    list_addItem(symb_list, "(");
    list_addItem(symb_list, ")");
    list_addItem(symb_list, "[");
    list_addItem(symb_list, "]");
    list_addItem(symb_list, ".");
    list_addItem(symb_list, ",");
    list_addItem(symb_list, ";");
    list_addItem(symb_list, "+");
    list_addItem(symb_list, "-");
    list_addItem(symb_list, "/");
    list_addItem(symb_list, "&");
    list_addItem(symb_list, "|");
    list_addItem(symb_list, "<");
    list_addItem(symb_list, ">");
    list_addItem(symb_list, "=");
    list_addItem(symb_list, "_");
    return symb_list;
}

LinkedList getTokenList() {
    return token_list;
}

char *getNextToken() {
    if(token_list != NULL) {
        char *token = token_list->data;
        token_list = token_list->next;
        return token;
    }
    return NULL;
}
