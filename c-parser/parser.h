// cooke_parser.h
#ifndef COOKE_PARSER_H
#define COOKE_PARSER_H

void parseProgram();
void parseStatement();
void parseCondition();
void parseExpression();
void parseTerm();
void parseFactor();
void parseOperator();
void match(int expected);
void syntaxError(const char* expected);
const char* getTokenName(int token);

#endif
