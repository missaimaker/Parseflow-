//cooke_parser.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "front.h"
#include "parser.h"

FILE *in_fp;
extern int currentLine;


const char* getTokenName(int token);
void syntaxError(const char* expected);

void match(int expected) {
    if (nextToken == expected) {
        lex();
    } else {
        syntaxError(getTokenName(expected));
    }
}

void syntaxError(const char* expected) {
    printf("Error encounter on line %d: The next lexeme was '%s' and the next token was %s\n",
            currentLine, lexeme, getTokenName(nextToken));
    exit(1);
}

const char* getTokenName(int token) {
    switch (token) {
        case INT_LIT:
            return "INT_LIT";
        case IDENT:
            return "IDENT";
        case ASSIGN_OP:
            return "ASSIGN_OP";
        case ADD_OP:
            return "ADD_OP";
        case SUB_OP:
            return "SUB_OP";
        case MULT_OP:
            return "MULT_OP";
        case DIV_OP:
            return "DIV_OP";
        case LEFT_PAREN:
            return "LEFT_PAREN";
        case RIGHT_PAREN:
            return "RIGHT_PAREN";
        case LESSER_OP:
            return "LESSER_OP";
        case GREATER_OP:
            return "GREATER_OP";
        case EQUAL_OP:
            return "EQUAL_OP";
        case NEQUAL_OP:
            return "NEQUAL_OP";
        case LEQUAL_OP:
            return "LEQUAL_OP";
        case GEQUAL_OP:
            return "GEQUAL_OP";
        case POW_OP:
            return "POW_OP";
        case INC_OP:
            return "INC_OP";
        case DEC_OP:
            return "DEC_OP";
        case SEMICOLON:
            return "SEMICOLON";
        case COLON:
            return "COLON";
        case KEY_READ:
            return "KEY_READ";
        case KEY_PRINT:
            return "KEY_PRINT";
        case KEY_IF:
            return "KEY_IF";
        case KEY_ELSE:
            return "KEY_ELSE";
        case KEY_BEGIN:
            return "KEY_BEGIN";
        case KEY_END:
            return "KEY_END";
        default:
            return "UNKNOWN";
    }
}

void parseProgram() {
    parseStatement();
    if (nextToken != EOF) {
        syntaxError("EOF");
    }
    printf("Syntax Validated\n");
    exit(0);
}

void parseStatement() {
    if (nextToken == IDENT) {
        lex();
        match(ASSIGN_OP);
        parseExpression();
    } else if (nextToken == INC_OP || nextToken == DEC_OP) {
        parseOperator();
    } else if (nextToken == KEY_READ) {
        lex();
        match(LEFT_PAREN);
        match(IDENT);
        match(RIGHT_PAREN);
    } else if (nextToken == KEY_PRINT) {
        lex();
        match(LEFT_PAREN);
        parseExpression();
        match(RIGHT_PAREN);
    } else if (nextToken == KEY_IF) {
        lex();
        parseCondition();
        match(COLON);
        match(KEY_BEGIN);
        parseStatement();
        if (nextToken == KEY_END) {
            lex();
        } else if (nextToken == KEY_ELSE) {
            lex();
            match(COLON);
            parseStatement();
            match(KEY_END);
        } else {
            syntaxError("KEY_END or KEY_ELSE");
        }
    } else {
        syntaxError("statement");
    }

    if (nextToken == SEMICOLON) {
        lex();
        parseStatement();
    }
}

void parseCondition() {
    parseExpression();
    switch (nextToken) {
        case LESSER_OP: case GREATER_OP: case EQUAL_OP:
        case NEQUAL_OP: case LEQUAL_OP: case GEQUAL_OP:
            lex();
            break;
        default:
            syntaxError("comparison operator");
    }
    parseExpression();
}

void parseExpression() {
    parseTerm();
    while (nextToken == ADD_OP || nextToken == SUB_OP) {
        lex();
        parseTerm();
    }
}

void parseTerm() {
    parseFactor();
    while (nextToken == MULT_OP || nextToken == DIV_OP || nextToken == POW_OP) {
        lex();
        parseFactor();
    }
}

void parseFactor() {
    if (nextToken == IDENT || nextToken == INT_LIT) {
        lex();
    } else if (nextToken == LEFT_PAREN) {
        lex();
        parseExpression();
        match(RIGHT_PAREN);
    } else {
        syntaxError("factor");
    }
}

void parseOperator() {
    if (nextToken == INC_OP || nextToken == DEC_OP) {
        lex();
        match(IDENT);
    } else {
        syntaxError("increment/decrement operator");
    }
}

int main(int argc, char *argv[]) {
    printf("Cooke Parser :: R11846096\n");

    if (argc != 2) {
        printf("usage: %s <path_to_source_file>\n", argv[0]);
        return 2;
    }

    in_fp = fopen(argv[1], "r");
    if (in_fp == NULL) {
        printf("ERROR - cannot open %s\n", argv[1]);
        return 3;
        
    }

    getChar();
    lex();
    parseProgram();

    fclose(in_fp);
    return 0;
}
