cmake_minimum_required(VERSION 3.16)
project(VM_Translator C)

set(CMAKE_C_STANDARD 99)

add_executable(VM_Translator main.c Parser.h Parser.c CodeWriter.h
        CodeWriter.c HellpeingFunctions.h HellpeingFunctions.c
        SymbolTable.h SymbolTable.c HashTable/HashTable.h HashTable/HashTable.c
        VM_Languange/Memory_Access_Comands.h VM_Languange/Memory_Access_Comands.c
        VM_Languange/Arithmetic_Logical_Commands.h VM_Languange/Arithmetic_Logical_Commands.c
        VM_Languange/Branching_Commands.h VM_Languange/Branching_Commands.c
        VM_Languange/Function_Commands.h VM_Languange/Function_Commands.c)