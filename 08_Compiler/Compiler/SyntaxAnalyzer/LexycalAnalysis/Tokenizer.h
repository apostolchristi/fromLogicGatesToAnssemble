//
// Created by Toor on 6/1/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../HellpingFunctions.h"
#include "Tokens_Table.h"
#include "Token_Parser.h"



#ifndef COMPILER_TOKENIZER_H
#define COMPILER_TOKENIZER_H



/* ----------------------> API Methods <---------------------------*/

/** Opens the input file/stream and gets ready to tokenize it. */
void TokenizerConstructor();
void Tokenizer_destructor();


void Tokenizer_initializer(char *input);


/** Do we have more tokens in the input? */
bool hasMoreTokens(FILE *input_file, FILE *output_file);

/** Gets the next token from the input and makes it the current token.
    This method should only be called if hasMoreTokens() is true.
    Initially there is no current token.
*/
char *Tokenizer_advance(char *input_file_line, FILE *output_file);

/** Returns the type of the current token.
 * KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST
 * */
char *tokenType(char *token);

/** Returns the keyword which is the current token.
    Should be called only when tokenType() is KEYWORD.
*/
char *keyWord();

/** Returns the character which is the current token.
    Should be called only when tokenType() is SYMBOL
*/
char *symbol();

/** Returns the identifier which is the current token.
    Should be called only when tokenType() is IDENTIFIER
*/
char *identifier();

/** Returns the integer value of the current token.
    Should be called only when tokenType() is INT_CONST
*/
int intVal();


/* ----------------------> Private Methods <---------------------------*/




#endif //COMPILER_TOKENIZER_H
