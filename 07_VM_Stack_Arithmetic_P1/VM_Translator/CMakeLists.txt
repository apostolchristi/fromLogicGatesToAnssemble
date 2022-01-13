cmake_minimum_required(VERSION 3.16)
project(VM_Translator C)

set(CMAKE_C_STANDARD 99)

add_executable(VM_Translator main.c Parser.h Parser.c CodeWriter.h
        CodeWriter.c HellpeingFunctions.h HellpeingFunctions.c)