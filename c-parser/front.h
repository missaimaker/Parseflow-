/* Project 1 Lexical Analyzer */
/* Medhawi Niroula - R11846096 */

#ifndef FRONT_H
#define FRONT_H

/* Character Classes */
#define LETTER 0    // Represents a letter (A-Z, a-z)
#define DIGIT 1     // Represents a digit (0-9)
#define UNKNOWN 99  // Represents an unknown character type

/* Token Codes */
#define INT_LIT 10       // Integer literal
#define IDENT 11         // Identifier (variable names, etc.)
#define ASSIGN_OP 12     // Assignment operator (':=')
#define ADD_OP 13        // Addition operator ('+')
#define SUB_OP 14        // Subtraction operator ('-')
#define MULT_OP 15       // Multiplication operator ('*')
#define DIV_OP 16        // Division operator ('/')
#define LEFT_PAREN 17    // Left parenthesis ('(')
#define RIGHT_PAREN 18   // Right parenthesis (')')
#define LESSER_OP 19     // Less than operator ('<')
#define GREATER_OP 20    // Greater than operator ('>')
#define EQUAL_OP 21      // Equal to operator ('=')
#define NEQUAL_OP 22     // Not equal to operator ('<>')
#define LEQUAL_OP 23     // Less than or equal to ('<=')
#define GEQUAL_OP 24     // Greater than or equal to ('>=')
#define POW_OP 25        // Power operator ('**')
#define INC_OP 26        // Increment operator ('++')
#define DEC_OP 27        // Decrement operator ('--')
#define SEMICOLON 28     // Semicolon (';')
#define COLON 29         // Colon (':')
#define KEY_READ 30      // Keyword 'read'
#define KEY_PRINT 31     // Keyword 'print'
#define KEY_IF 32        // Keyword 'if'
#define KEY_ELSE 33      // Keyword 'else'
#define KEY_BEGIN 34     // Keyword 'begin'
#define KEY_END 35       // Keyword 'end'


const char* getTokenName(int token);
extern int nextToken;
extern char lexeme[100];




/* Function Prototypes */
int lex(void);  // Function prototype for lexical analyzer
void getChar(void);

#endif  // End of FRONT_H