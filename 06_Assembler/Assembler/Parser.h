//
// Created by Toor on 11/24/2021.
//


/**
 * Encapsulates access to the input code.
 * Reads an assembly language command, parses it, and provides convenient access to the command’s components(fields and symbols).
 * In addition, removes all white space and comments.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include "SymbolTable.h"
#include "Code.h"
#include "HashTable/HashTable.h"

#define BITS_16 16 /* max array length */

void constructor_Parser();
void destructor_Parser();

/* Opens the input file/stream and gets ready to parse it.
 */
void initializer(char const *input_file_dest, char const* output_file_dest);


/* Reads the next command from the input and makes it the current command.
 * Should be called only if hasMoreCommands() is true.
 * Initially there is no current command.
 */
char *advance(char *input_file_line);

/* Checks if there are more commands in the input
 */
bool hasMoreCommands(char *input_file_line, FILE *file_in);


/* Removes all white space, comments and all unnecessary symbols.
 * This function should be improved because I didn't pay much attention to all possible case scenarios of an incoming string.
 * So it might be a potential place for bugs.
 */
bool reshape_theCommand(const char *input_file_line, char *command);


/* Returns the type of the current command:
 *  - A_COMMAND for @Xxx where Xxx is either a symbol or a decimal number
 *  - C_COMMAND for dest = comp ; jump
 *  - L_COMMAND(actually, pseudo-command) for(Xxx) where Xxx is a symbol
 */
char *commandType(char *command);


/* Returns the symbol or decimal Xxx of the current command @Xxxor(Xxx).
 * Should be called only when commandType()is A_COMMAND or L_COMMAND.
 */
void parse_symbols(char *command, size_t *length);


/* Returns the dest mnemonic in the current C-command (8 possibilities).
 * Should be called only when commandType() is C_COMMAND.
 */
void parse_dest(char const *command, char *mnemonic);


/* Returns the comp mnemonic in the currentC-command (28 possibilities).
 * Should be called only when commandType()isC_COMMAND
 */
void parse_comp(char const *command, char *mnemonic);


/* Returns the jump mnemonic in the current C-command (8 possibilities).
 * Should be called only when commandType()is C_COMMAND.
 */
void parse_jump(char const *command, char *mnemonic);
