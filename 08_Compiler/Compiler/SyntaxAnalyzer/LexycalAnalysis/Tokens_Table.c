//
// Created by Toor on 6/9/2022.
//

#include "Tokens_Table.h"
#define K_SIZE 21
#define S_SIZE 19

static List *keyword_list;
static List *symbol_list;


void TokensTable_constructor() {

    if(keyword_list == NULL) {
        keyword_list = initialize_keywords();
    }

    if(symbol_list == NULL) {
        symbol_list = initialize_symbols();
    }
}


void TokensTable_destructor() {
    if(keyword_list != NULL) {
        list_delete(keyword_list);
        keyword_list = NULL;
    }

    if(symbol_list != NULL) {
        list_delete(symbol_list);
        keyword_list = NULL;
    }
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


List *initialize_keywords() {

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


List *initialize_symbols() {

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


