//
// Created by Toor on 6/1/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "TokenCode.h"
#include "../Parser/CompilationEngine.h"
#include "../../DataStructure/HashTable.h"
#include "../../DataStructure/LinkedList.h"


#ifndef COMPILER_TOKENIZER_H
#define COMPILER_TOKENIZER_H


/** Opens the input file/stream and gets ready to tokenize it. */
void Tokenizer_initializer(char const *input);

/** Do we have more tokens in the input? */
bool hasMoreTokens(FILE *input_file);

/** Gets the next token from the input and makes it the current token.
    This method should only be called if hasMoreTokens() is true.
    Initially there is no current token.
*/
void Tokenizer_advance();

/** Returns the type of the current token.
 * KEYWORD, SYMBOL, IDENTIFIER, INT_CONST, STRING_CONST
*/
char *tokenType(char *token);



#endif //COMPILER_TOKENIZER_H
