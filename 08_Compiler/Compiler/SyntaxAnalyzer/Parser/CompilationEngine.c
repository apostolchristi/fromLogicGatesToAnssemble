//
// Created by Toor on 6/21/2022.
//

#include "CompilationEngine.h"

FILE *output_file = NULL;
char *current_token;
char *token_type;
List *keywordconstant_list;
List *op_list;


void CompilationEngine_constructor(char *file_pathName) {

    output_file = openFile(file_pathName, "w");
    keywordconstant_list = list_create(4);
    op_list = list_create(9);

    list_addItem(keywordconstant_list, "true");
    list_addItem(keywordconstant_list, "false");
    list_addItem(keywordconstant_list, "null");
    list_addItem(keywordconstant_list, "this");
    list_addItem(op_list, "+");
    list_addItem(op_list, "-");
    list_addItem(op_list, "*");
    list_addItem(op_list, "/");
    list_addItem(op_list, "=");
    list_addItem(op_list, "<");
    list_addItem(op_list, ">");
    list_addItem(op_list, "&");
    list_addItem(op_list, "|");

    compileClass();
    CompilationEngine_destructor();
}


void CompilationEngine_destructor() {

    fclose(output_file);
    list_delete(keywordconstant_list);
    list_delete(op_list);
}


/* ---------------------------------------------Program structure------------------------------------------------------*/

/* class: 'class' className '{' classVarDec* subroutineDec* '}' */
void compileClass() {

    char *nonTerminal_CLASS_openTag = "<class>\n";
    char *nonTerminal_CLASS_closeTag = "</class>\n";

    //'class'
    if (strcmp(current_token = getNextToken(), "class") == 0) {
        fputs(nonTerminal_CLASS_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //className
        eatIdentifierName();

        //'{'
        eatLeftCurlyBraceSymbol();

        //classVarDec*
        while (strcmp(current_token, "field") == 0 || strcmp(current_token, "static") == 0) {
            compileClassVarDec();
        }

        //subroutineDec*
        while (strcmp(current_token, "constructor") == 0 || strcmp(current_token, "function") == 0 ||
               strcmp(current_token, "method") == 0) {
            compileSubroutineDec();
        }

        //'}'
        eatRightCurlyBraceSymbol();

        if (current_token == NULL) {
            fputs(nonTerminal_CLASS_closeTag, output_file);
        } else {
            printf("error: there are more tokens to be eaten. Check the %s\n", __func__ );
            exit(0);
        }
    } else {
        printf("error: unknown type name '%s'; did u mean 'class'?\n", current_token);
        exit(0);
    }


}

/* classVarDec: ('static'|'field') type varName(','varname)* ';' */
void compileClassVarDec() {

    char *nonTerminal_CLASSVARDEC_openTag = "<classVarDec>\n";
    char *nonTerminal_CLASSVARDEC_closeTag = "</classVarDec>\n";

    //('static'|'field')
    if (strcmp(current_token, "field") == 0 || strcmp(current_token, "static") == 0) {
        fputs(nonTerminal_CLASSVARDEC_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //type
        if (isType() == true) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();
        } else {
            printf("error: unknown type name '%s'; expected type is 'int','bool','char' or 'className'.\n",
                   current_token);
            exit(0);
        }

        //varName(','varname)*
        eatMultipleVarName();

        //';'
        eatSemicolonSymbol();

        fputs(nonTerminal_CLASSVARDEC_closeTag, output_file);
    } else {
        return;
    }
}


/* subroutineDec: ('constructor'|'function'|'method') ('void'|type) subroutineName '(' parameterList ')' subroutineBody */
void compileSubroutineDec() {

    char *nonTerminal_SUBROUTINEDEC_openTag = "<subroutineDec>\n";
    char *nonTerminal_SUBROUTINEDEC_closeTag = "</subroutineDec>\n";

    //('constructor'|'function'|'method')
    if (strcmp(current_token, "constructor") == 0 || strcmp(current_token, "function") == 0 ||
        strcmp(current_token, "method") == 0) {
        fputs(nonTerminal_SUBROUTINEDEC_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //('void'|type)
        if (strcmp(current_token, "void") == 0 || isType() == true) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();
        } else {
            printf("error: unknown type name '%s'; expected type is 'void' or 'int','bool','char', 'className'. \n",
                   current_token);
            exit(0);
        }

        //subroutineName
        eatIdentifierName();

        //'(' parameterList ')' - parameterList - is optional so no need for 'else' statement
        eatLeftParenthesisSymbol();
        if (strcmp(current_token, ")") != 0) {
            compileParameterList();
        }
        eatRightParenthesisSymbol();

        //subroutineBody
        compileSubroutineBody();

        fputs(nonTerminal_SUBROUTINEDEC_closeTag, output_file);
    } else {
        return;
    }
}


/* subroutineBody: '{' varDec* statements '}' */
void compileSubroutineBody() {

    char *nonTerminal_SUBROUTINEBODY_openTag = "<subroutineBody>\n";
    char *nonTerminal_SUBROUTINEBODY_closeTag = "</subroutineBody>\n";

    //'{'
    eatLeftCurlyBraceSymbol();

    fputs(nonTerminal_SUBROUTINEBODY_openTag, output_file);

    //varDec*
    compileVarDec();


    //statements
    compileStatements();

    //'}'
    eatRightCurlyBraceSymbol();

    fputs(nonTerminal_SUBROUTINEBODY_closeTag, output_file);
}


/* varDec: 'var' type varName(',' varName)* ';' */
void compileVarDec() {
    char *nonTerminal_VARDEC_openTag = "<varDec>\n";
    char *nonTerminal_VARDEC_closeTag = "</varDec>\n";

    //var
    if (strcmp(current_token, "var") == 0) {
        fputs(nonTerminal_VARDEC_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //type
        if (isType() == true) {
            fputs(terminalTagBuilder(current_token, token_type), output_file);
            current_token = getNextToken();
        } else {
            printf("error: unknown type name '%s'; expected type is 'int','bool','char' or 'className'.\n",
                   current_token);
            exit(0);
        }

        //varName(',' varName)*
        eatMultipleVarName();

        //';'
        eatSemicolonSymbol();

        fputs(nonTerminal_VARDEC_closeTag, output_file);
    } else {
        return;
    }

}

/* ( (type varName) (',' type varName)* )? */
void compileParameterList() {

    char *nonTerminal_PARAMETERLIST_openTag = "<parameterList>\n";
    char *nonTerminal_PARAMETERLIST_closeTag = "</parameterList>\n";

    fputs(nonTerminal_PARAMETERLIST_openTag, output_file);

    //(type varName)
    start:
    if (isType() == true) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);
        current_token = getNextToken();

        //varName
        eatIdentifierName();

        //(',' type varName)*
        if (strcmp(current_token, ",") == 0) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();
            goto start;
        }

        fputs(nonTerminal_PARAMETERLIST_closeTag, output_file);
    } else {
        return;
    }
}


/* -----------------------------------------------Statements--------------------------------------------------------*/


void compileStatements() {

    while (strcmp(current_token, "let") == 0 || strcmp(current_token, "if") == 0 ||
           strcmp(current_token, "while") == 0 || strcmp(current_token, "do") == 0) {

        if (strcmp(current_token, "let") == 0) {
            compileLet();
        } else if (strcmp(current_token, "if") == 0) {
            compileIf();
        } else if (strcmp(current_token, "while") == 0) {
            compileWhile();
        } else if (strcmp(current_token, "do") == 0) {
            compileDo();
        }  else {
            printf("Something went wrong at:%s\n", __func__);
            exit(0);
        }
    }

    if (strcmp(current_token, "return") == 0) {
        compileReturn();
    }
}


/* letStatement: 'let' varName('[' expression ']')? '=' expression ';' */
void compileLet() {

    char *nonTerminal_LETSTATEMENT_openTag = "<letStatement>\n";
    char *nonTerminal_LETSTATEMENT_closeTag = "</letStatement>\n";

    //'let'
    if (strcmp(current_token, "let") == 0) {
        fputs(nonTerminal_LETSTATEMENT_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //varName
        eatIdentifierName();

        //('[' expression ']')? - this part is optional
        if (strcmp(current_token, "[") == 0) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();

            compileExpression();

            if (strcmp(current_token, "]") == 0) {
                fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
                current_token = getNextToken();
            } else {
                printf("error: expected ']' but no such a symbol '%s';?\n", current_token);
                exit(0);
            }
        }

        //'='
        eatEqualSymbol();

        //expression
        compileExpression();

        //';'
        eatSemicolonSymbol();

        fputs(nonTerminal_LETSTATEMENT_closeTag, output_file);
    } else {
        printf("error: unknown type name '%s'; did u mean 'let'?\n", current_token);
        exit(0);
    }
}

/* ifStatement: 'if' '(' expression ')' '{' statements '}' ('else' '{' statements '}')? */
void compileIf() {
    char *nonTerminal_IFSTATEMENT_openTag = "<ifStatement>\n";
    char *nonTerminal_IFSTATEMENT_closeTag = "</ifStatement>\n";

    //'if'
    if (strcmp(current_token, "if") == 0) {
        fputs(nonTerminal_IFSTATEMENT_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //'(' expression ')'
        eatLeftParenthesisSymbol();
        compileExpression();
        eatRightParenthesisSymbol();

        //'{' statements '}'
        eatLeftCurlyBraceSymbol();
        compileStatements();
        eatRightCurlyBraceSymbol();

        //('else' '{' statements '}')? - this one is optional
        if (strcmp(current_token, "else") == 0) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();

            eatLeftCurlyBraceSymbol();
            compileStatements();
            eatRightCurlyBraceSymbol();
        }

        fputs(nonTerminal_IFSTATEMENT_closeTag, output_file);
    } else {
        printf("error: unknown keyword '%s'; did u mean 'if'?\n", current_token);
        exit(0);
    }
}


/* whileStatement: 'while' '(' expression ')' '{' statements '}'  */
void compileWhile() {

    char *nonTerminal_WHILESTATEMENT_openTag = "<whileStatement>\n";
    char *nonTerminal_WHILESTATEMENT_closeTag = "</whileStatement>\n";

    // 'while'
    if (strcmp(current_token, "while") == 0) {
        fputs(nonTerminal_WHILESTATEMENT_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //'(' expression ')'
        eatLeftParenthesisSymbol();
        compileExpression();
        eatRightParenthesisSymbol();

        //'{' statements '}'
        eatLeftCurlyBraceSymbol();
        compileStatements();
        eatRightCurlyBraceSymbol();

        fputs(nonTerminal_WHILESTATEMENT_closeTag, output_file);
    } else {
        printf("error: unknown keyword '%s'; did u mean 'while'?\n", current_token);
        exit(0);
    }
}

/* doStatement: 'do' subroutineCall ';' */
void compileDo() {

    char *nonTerminal_DOSTATEMENT_openTag = "<doStatement>\n";
    char *nonTerminal_DOSTATEMENT_closeTag = "</doStatement>\n";

    // 'do'
    if (strcmp(current_token, "do") == 0) {
        fputs(nonTerminal_DOSTATEMENT_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //subroutineCall ';'
        compileSubroutineCall(NULL);
        eatSemicolonSymbol();

        fputs(nonTerminal_DOSTATEMENT_closeTag, output_file);
    } else {
        printf("error: unknown keyword '%s'; did u mean 'do'?\n", current_token);
        exit(0);
    }
}


/* returnStatement: 'return' expression? ';'  */
void compileReturn() {

    char *nonTerminal_RETURNSTATEMENT_openTag = "<returnStatement>\n";
    char *nonTerminal_RETURNSTATEMENT_closeTag = "</returnStatement>\n";

    // 'return'
    if (strcmp(current_token, "return") == 0) {
        fputs(nonTerminal_RETURNSTATEMENT_openTag, output_file);

        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();

        //expression?
        if (strcmp(current_token, ";") != 0) {
            compileExpression();
        }

        //';'
        eatSemicolonSymbol();

        fputs(nonTerminal_RETURNSTATEMENT_closeTag, output_file);
    } else {
        printf("error: unknown keyword '%s'; did u mean 'return'?\n", current_token);
        exit(0);
    }
}


/* -----------------------------------------------Expressions--------------------------------------------------------*/

/* expression: term (op term)* */
void compileExpression() {

    char *nonTerminal_EXPRESSION_openTag = "<expression>\n";
    char *nonTerminal_EXPRESSION_closeTag = "</expression>\n";

    fputs(nonTerminal_EXPRESSION_openTag, output_file);

    //term
    compileTerm();

    //(op term)*
    if (isOp() == true) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        compileTerm();
    }

    fputs(nonTerminal_EXPRESSION_closeTag, output_file);
}

/* term: integerConstant | stringConstant | keywordConstant | varName |
        varName '[' expression ']' | subroutineCall | '(' expression ')' |
        unaryOp term
        */
void compileTerm() {

    char *nonTerminal_TERM_openTag = "<term>\n";
    char *nonTerminal_TERM_closeTag = "</term>\n";
    char *next_token = NULL;

    token_type = tokenType(current_token);
    next_token = getNextToken();
    fputs(nonTerminal_TERM_openTag, output_file);
    fputs(nonTerminal_TERM_closeTag, output_file);

    // varName '[' expression ']'
    if (strcmp(token_type, "identifier") == 0 && strcmp(next_token, "[") == 0) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);
        fputs(terminalTagBuilder(next_token, tokenType(next_token)), output_file);
        current_token = getNextToken();
        compileExpression();
        if (strcmp(current_token, "]") == 0) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();
        } else {
            printf("error: expected ']' but no such a symbol '%s';?\n", current_token);
            exit(0);
        }
    }

        // | subroutineCall
    else if (strcmp(token_type, "identifier") == 0 && (strcmp(next_token, "(") == 0 || strcmp(next_token, ".") == 0)) {
        compileSubroutineCall(next_token);
        return;
    }

        //integerConstant | stringConstant | keywordConstant | varName
    else if (strcmp(token_type, "intConst") == 0 || strcmp(token_type, "stringConst") == 0 ||
             strcmp(token_type, "identifier") == 0 || list_lookup(keywordconstant_list, current_token) == true) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);
        strcpy(current_token, next_token);
        return;
    }

        //'(' expression ')'
    else if (strcmp(current_token, "(") == 0) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);
        strcpy(current_token, next_token);
        compileExpression();
        eatRightParenthesisSymbol();
        return;
    }

        //| unaryOp term
    else if (strcmp(current_token, "-") == 0 || strcmp(current_token, "~") == 0) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);
        strcpy(current_token, next_token);
        compileTerm();
        return;
    }


}

/* subroutineCall: subroutineName '(' expressionList ')' | (className|varName) '.'
                    subroutineName '(' expressionList ')'  */
void compileSubroutineCall(char *next_token) {

    //subroutineName | (className|varName)
    if (strcmp(tokenType(current_token), "identifier") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);

        if (next_token == NULL) {
            current_token = getNextToken();
        } else {
            strcpy(current_token, next_token);
        }

        //'(' expressionList ')'
        if (strcmp(current_token, "(") == 0) {
            eatLeftParenthesisSymbol();
            compileExpressionList();
            eatRightParenthesisSymbol();
            return;
        }
    }

    //'.' subroutineName '(' expressionList ')'
    if (strcmp(current_token, ".") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
        compileSubroutineCall(NULL);
        return;
    }

    printf("Something went wrong at:%s\n", __func__);
    exit(0);
}


/*expressionList: (expression (',' expression)*)? */
void compileExpressionList() {

    char *nonTerminal_EXPRESSIONLIST_openTag = "<expressionList>\n";
    char *nonTerminal_EXPRESSIONLIST_closeTag = "</expressionList>\n";

    if (strcmp(current_token, ")") != 0) {

        fputs(nonTerminal_EXPRESSIONLIST_openTag, output_file);

        //expression
        compileExpression();

        //(',' expression)*)
        while (strcmp(current_token, ",") == 0) {
            fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
            current_token = getNextToken();
            compileExpression();
        }

        fputs(nonTerminal_EXPRESSIONLIST_closeTag, output_file);
    } else {
        return;
    }
}


/* -----------------------------------------------Routine--------------------------------------------------------*/


/* type: 'int'|'char'|'boolean'|className */
bool isType() {

    if (strcmp(current_token, "int") == 0 || strcmp(current_token, "char") == 0 ||
        strcmp(current_token, "boolean") == 0 || strcmp(token_type, "identifier") == 0) {
        return true;
    }
    return false;
}

bool isOp() {

    if (list_lookup(op_list, current_token)) {
        return true;
    }
    return false;
}


void eatSemicolonSymbol() {
    if (strcmp(current_token, ";") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
    } else {
        printf("error: expected ';' but no such a symbol '%s';?\n", current_token);
        exit(0);
    }
}

/* Identifier: - a sequence of letters, digits, and underscore ('_') not starting with a digit
 * className: identifier
 * subroutineName: identifier
 * varName: identifier
 */
void eatIdentifierName() {

    if (strcmp(token_type = tokenType(current_token), "identifier") == 0) {
        fputs(terminalTagBuilder(current_token, token_type), output_file);

        current_token = getNextToken();
    } else {
        printf("error: unknown identifier name '%s'; did u mean '' ?\n", current_token);
        exit(0);
    }
}

void eatEqualSymbol() {
    if (strcmp(current_token, "=") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);

        current_token = getNextToken();
    } else {
        printf("error: expected '=' but no such a symbol '%s';?\n", current_token);
        exit(0);
    }
}

/* varName(','varname)* */
void eatMultipleVarName() {

    //varName
    eatIdentifierName();

    //(','varname)*
    if (strcmp(current_token, ",") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);

        current_token = getNextToken();
        eatMultipleVarName();
    }
}


void eatLeftParenthesisSymbol() {
    if (strcmp(current_token, "(") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
    } else {
        printf("error: unknown symbol '%s'; did u mean '('?\n", current_token);
        exit(0);
    }
}


void eatRightParenthesisSymbol() {
    if (strcmp(current_token, ")") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
    } else {
        printf("error: unknown symbol '%s'; did u mean ')'?\n", current_token);
        exit(0);
    }
}


void eatLeftCurlyBraceSymbol() {
    if (strcmp(current_token, "{") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
    } else {
        printf("error: unknown symbol '%s'; did u mean '{'?\n", current_token);
        exit(0);
    }
}


void eatRightCurlyBraceSymbol() {
    if (strcmp(current_token, "}") == 0) {
        fputs(terminalTagBuilder(current_token, tokenType(current_token)), output_file);
        current_token = getNextToken();
    } else {
        printf("error: unknown symbol '%s'; did u mean '}'?\n", current_token);
        exit(0);
    }
}