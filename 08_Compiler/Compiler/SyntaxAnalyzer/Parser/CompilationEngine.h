//
// Created by Toor on 6/21/2022.
//

#ifndef COMPILER_COMPILATIONENGINE_H
#define COMPILER_COMPILATIONENGINE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../DataStructure/LinkedList.h"
#include "../LexycalAnalysis/TokenCode.h"
#include "../LexycalAnalysis/Tokenizer.h"

/** Hints:

 * 'xxx' : quoted boldface is used to list language tokens that appear verbatim ("terminals");
 *  xxx : Regular typeface represents names on non-terminals;
 *  () : used for grouping;
 *  x | y : indicates that either x or y appear;
 *  x y : indicates that x appears, and then y appears;
 *  x? : indicates that x appears 0 or 1 times;
 *  x* : indicates that x appears 0 or more times.


 * Non-Terminals = whenever a non-terminal language element of type xxx is encountered,
    the syntax analyzer should generate the marked-up output:

    <xxx>Recursive code for the body of the xxx element.</xxx>

    WHERE xxx is:
    - class, classVarDec, subroutineDec, parameterList, subroutineBody, varDec;
    - statements, whileStatement, ifStatement, returnStatement, letStatement, doStatement;
    - expression, term, expressionList.

 * Terminals = whenever a terminal language element of type xxx is encountered,
    the syntax analyzer should generate the marked-up output:

    <xxx>terminal</xxx>

    WHERE xxx is one of the five token types
    - keyword, symbol, integerConstant, stringConstant, or identifier.
*/


void CompilationEngine_constructor(char *file_pathName);
/* ---------------------------------------------Program structure------------------------------------------------------*/

/* Compiles a complete class. */
void compileClass();

/* Compiles a static declaration or a field declaration. */
void compileClassVarDec();

/* Compiles a complete method, function, or constructor. */
void compileSubroutineDec();

/* Compiles a (possibly empty) parameter list, not including the enclosing "()". */
void compileParameterList();

/* Compiles a "var" declaration. */
void compileVarDec();

void compileSubroutineBody();


/* -----------------------------------------------Statements--------------------------------------------------------*/

/* Compiles a sequence of statements, not including the enclosing "{}". */
void compileStatements();

/* Compiles a "do" statement. */
void compileDo();

/* Compiles a "let" statement. */
void compileLet();

/* Compiles a "while" statement. */
void compileWhile();

/* Compiles a "return" statement. */
void compileReturn();

/* Compiles a "if" possibly with a trailing "else" clause. */
void compileIf();

/* -----------------------------------------------Expressions--------------------------------------------------------*/


/* Compiles an expression. */
void compileExpression();

/* Compiles a term.
 * This routine is faced with a slight difficulty when trying to decide between some of the alternative parsing rules.
 * Specifically, if the current token is an identifier, the routine must distinguish between a variable, an array entry,
    and a subroutine call.
 * A single lookahead token, which may be one of "[", "(" or "." suffices to distinguish between the three possibilities.
 * Any other token is not part of this term and should not be advanced over.


 The rule will parse successfully an empty parameter list, since the question mark at the end of the right hand-side
 indicates that the parameter list may or may not apper.
 *  parameterList: ( ( type varName )   ( ‘,’ type varName ) * ) ?
*/
void compileTerm();

void compileSubroutineCall();

/* Compiles a (possibly empty) comma-separated list of expressions. */
void compileExpressionList();


/* -----------------------------------------------Routine--------------------------------------------------------*/
bool isType();
bbool isOp();
void eatMultipleVarName();
void eatSemicolonSymbol();
void eatEqualSymbol();
void eatIdentifierName();
void eatLeftParenthesisSymbol();
void eatRightParenthesisSymbol();
void eatLeftCurlyBraceSymbol();
void eatRightCurlyBraceSymbol();

#endif //COMPILER_COMPILATIONENGINE_H

