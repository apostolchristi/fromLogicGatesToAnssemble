//
// Created by Toor on 1/12/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include "HellpeingFunctions.h"
#include "CodeWriter.h"


#ifndef VM_TRANSLATOR_PARSER_H
#define VM_TRANSLATOR_PARSER_H

/* Opens the input file/stream and gets ready to parse it.
 */
void initializer(char const *input_file_dest, char const* output_file_dest);

/* Checks if there are more commands in the input
 */
bool hasMoreCommands(char *input_file_line, FILE *file_in);


/* Reads the next command from the input and makes it the current command.
 * Should be called only if hasMoreCommands() is true.
 * Initially there is no current command.
 */
char *advance(char *input_file_line, char const *input_file_name);

char *commandType(char *command);

/* Returns the first argument of the current command. In the case of C_ARITHMETIC, the command itself (add, sub, etc.) is returned.
 * Should not be called if the current command is C_RETURN */
void parse_arg1(char const *command, char const *command_type, char *arg1);

char *parse_arg2(char const *command);

char *add_comments(char *current_command, char *segment_assembly_code);





/* Removes all white space, comments and all unnecessary symbols.
 * This function should be improved because I didn't pay much attention to all possible case scenarios of an incoming string.
 * So it might be a potential place for bugs.
 */
bool reshape_theCommand(const char *input_file_line, char *command);

#endif //VM_TRANSLATOR_PARSER_H
