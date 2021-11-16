cmake_minimum_required(VERSION 3.16)
project(Assembler C)

set(CMAKE_C_STANDARD 99)

#set (SOURCE_FILES )

add_executable(Assembler main.c Parser.h Code.h Parser.c SymbolTable.h SymbolTable.c HellperMethods.h HellperMethods.c HashTable/HashTable.h HashTable/HashTable.c)