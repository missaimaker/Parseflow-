/*
 * Project 1: Lexical Analyzer
 * Author: Medhawi Niroula
 * Rnumber: R11846096
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "front.h"
#define NUM_KEYWORDS 6

/*Global variable*/
int nextToken; 

/*Local Variables*/
static int charClass;
char lexeme [100];
static char nextChar;
static int lexLen;
static FILE *in_fp;
int currentLine = 1;

/*Local Function Declarations*/
void addChar();
void getChar();
void getNonBlank();

/*array of keywords*/
char *keywords[] = { "read", "print",  "if", "else", "begin", "end" };


/*lookup- a function to lookup operators and parentheses and return the * token */
static int lookup(char ch){
    switch (ch){
        case '(':
            addChar();
            nextToken= LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken= RIGHT_PAREN;
            break;
        case '+':
            addChar();
            getChar();
            if (nextChar =='+') /*Check for increment operator (++)*/
            {
                addChar();
                nextToken= INC_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= ADD_OP;
            }
            break;
        case '-':
            addChar();
            getChar();
            if (nextChar =='-') /*Check for decrement operator (--)*/
            {
                addChar();
                nextToken= DEC_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= SUB_OP;
            }
            break;
        case '*':
            addChar();
            getChar();
            if (nextChar =='*') /*check for power operator (**)*/
            {
                addChar();
            nextToken= POW_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= MULT_OP;
            }
            
            break;
        case '/':
            addChar();
            nextToken=DIV_OP;
            break;
        case ';':
            addChar();
            nextToken=SEMICOLON;
            break;
        case ':':
            addChar();
            getChar();
            if (nextChar =='=') /*check for assignment operator (:=)*/
            {
                addChar();
                nextToken= ASSIGN_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= COLON;
            }
                break;
            
        case '<':
            addChar();
            getChar();
            if (nextChar =='=') //check for less than equal operator (<=)
            {
                addChar();
                nextToken= LEQUAL_OP;
            } else if (nextChar == '>') //check for not equal operator (<>)
            {
                addChar();
                 nextToken = NEQUAL_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= LESSER_OP;
            }
                break;
            
        case '>':
            addChar();
            getChar();
            if (nextChar =='=') //check for greater than or equal operator (>=)
            {
                addChar();
            nextToken= GEQUAL_OP;
            } else
            {
                ungetc(nextChar, in_fp);
                nextToken= GREATER_OP;
            }
                break;
            
         case '=':
            addChar();
            nextToken= EQUAL_OP;
            break;
        default:
            addChar();
            nextToken= UNKNOWN;
            break;
    }
    return nextToken;
}

/*function to skip whitespace*/
void getNonBlank(){
    while (isspace (nextChar)) {
    getChar();
    if (nextChar == EOF) break;  // Avoid infinite loop at EOF
    }
}

/*function to check if an identifier is a keyword */
static int checkKeyword(char*ident){
    int i;
    for(i=0; i<NUM_KEYWORDS; i++){
        if (strcmp(ident, keywords [i])==0){
            switch (i) {
                case 0:
                    return KEY_READ;
                case 1:
                    return KEY_PRINT;
                case 2:
                    return KEY_IF; 
                case 3:
                    return KEY_ELSE;
                case 4:
                    return KEY_BEGIN;
                case 5: 
                    return KEY_END;


            }
    }
}
    return IDENT; /*return IDENT if it's not a keyword*/
}

/*addChar- a function to add nextChar to lexeme*/
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0' ;
    } else {
        printf("Error - Lexeme is too long\n");
    }
}

/*getChar- a function to get the next character input and determine its character class */
void getChar(){
    if ((nextChar=getc(in_fp)) !=EOF){
        if (isalpha(nextChar))
            charClass= LETTER;
        else if (isdigit(nextChar))
            charClass=DIGIT;
        else charClass= UNKNOWN;
    } else{
            charClass=EOF;
        }
}


/*lex- a simple lexical analyzer for arithmetic expressions*/
int lex(){
    lexLen= 0;
    getNonBlank();
    switch (charClass){
        case LETTER: 
            addChar();
            getChar();
            while (charClass==LETTER || charClass==DIGIT){
                addChar();
                getChar();
            }
            nextToken = checkKeyword(lexeme); 
            break;
    
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT){
                addChar();
                getChar();
            }
            nextToken = INT_LIT; 
            break;
        
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;
        
        case EOF:
                nextToken= EOF; 
                lexeme[0]= 'E';
                lexeme[1]= 'O';
                lexeme[2]= 'F';
                lexeme[3]= '\0';
                break;
    }
    
      /* Print lexeme and token name */
    if (nextToken != EOF) {
    printf("%s ", lexeme);
    switch (nextToken) {
        case 
            INT_LIT: printf("INT_LIT\n"); 
            break;
        case 
            IDENT: printf("IDENT\n");
            break;
        case 
            ASSIGN_OP: printf("ASSIGN_OP\n"); 
            break;
        case 
            ADD_OP: printf("ADD_OP\n"); 
            break;
        case 
            SUB_OP: printf("SUB_OP\n"); 
            break;
        case 
            MULT_OP: printf("MULT_OP\n"); 
            break;
        case 
            DIV_OP: printf("DIV_OP\n"); 
            break;
        case 
            LEFT_PAREN: printf("LEFT_PAREN\n"); 
            break;
        case 
            RIGHT_PAREN: printf("RIGHT_PAREN\n"); 
            break;
        case 
            LESSER_OP: printf("LESSER_OP\n"); 
            break;
        case 
            GREATER_OP: printf("GREATER_OP\n");
            break;
        case 
            EQUAL_OP: printf("EQUAL_OP\n"); 
            break;
        case 
            NEQUAL_OP: printf("NEQUAL_OP\n"); 
            break;
        case 
            LEQUAL_OP: printf("LEQUAL_OP\n"); 
            break;
        case 
            GEQUAL_OP: printf("GEQUAL_OP\n");
            break;
        case 
            POW_OP: printf("POW_OP\n"); 
            break;
        case 
            INC_OP: printf("INC_OP\n"); 
            break;
        case 
            DEC_OP: printf("DEC_OP\n"); 
            break;
        case 
            SEMICOLON: printf("SEMICOLON\n"); 
            break;
        case 
            COLON: printf("COLON\n"); 
            break;
        case 
            KEY_READ: printf("KEY_READ\n"); 
            break;
        case 
            KEY_PRINT: printf("KEY_PRINT\n"); 
            break;
        case 
            KEY_IF: printf("KEY_IF\n"); 
            break;
        case 
            KEY_ELSE: printf("KEY_ELSE\n"); 
            break;
        case 
            KEY_BEGIN: printf("KEY_BEGIN\n"); 
            break;
        case 
            KEY_END: printf("KEY_END\n"); 
            break;
        default: printf("UNKNOWN\n"); 
            break;
        }
    }
    return nextToken;

}
