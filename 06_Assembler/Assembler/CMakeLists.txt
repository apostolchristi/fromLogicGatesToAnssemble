cmake_minimum_required(VERSION 3.16)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c SymbolTable.h SymbolTable.c Parser.h Parser.c Code.h Code.c HellpeingFunctions.h HellpeingFunctions.c HashTable/HashTable.h HashTable/HashTable.c)