//
// Created by Toor on 1/12/2022.
//

#ifndef VM_TRANSLATOR_CODEWRITER_H
#define VM_TRANSLATOR_CODEWRITER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "SymbolTable.h"
#include "HellpeingFunctions.h"
#include "VM_Languange/Memory_Access_Comands.h"


char *memoryAccessSegmentType(char *mnemonic_arg1, char *mnemonic_arg2, char *file_name);

#endif //VM_TRANSLATOR_CODEWRITER_H
