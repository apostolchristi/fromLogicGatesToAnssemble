cmake_minimum_required(VERSION 3.16)

# set the project name
project(Compiler)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
set(SYNTAX_ANALYZER SyntaxAnalyzer/LexycalAnalysis/Tokenizer.h SyntaxAnalyzer/LexycalAnalysis/Tokenizer.c SyntaxAnalyzer/LexycalAnalysis/TokenCode.c SyntaxAnalyzer/LexycalAnalysis/TokenCode.h SyntaxAnalyzer/Parser/CompilationEngine.c SyntaxAnalyzer/Parser/CompilationEngine.h)

set(DATA_STRUCTURE DataStructure/HashTable.h DataStructure/HashTable.c
        DataStructure/List.h DataStructure/List.c
        DataStructure/LinkedList.h DataStructure/LinkedList.c)

# add the executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${DATA_STRUCTURE} ${SYNTAX_ANALYZER} )