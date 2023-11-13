/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages.
 * Pearson, 10th edition.
 *
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int nextToken;
FILE *in_fp;

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
//Peters added code
#define MOD_OP 22
#define OR_OP 34
#define LESS_OP 25
#define LESSEQUAL_OP 26
#define GREATER_OP 27
#define GREATEREQUAL_OP 28
#define EQUAL_OP 29
#define NOTEQUAL_OP 30
#define AND_OP 23

/******************************************************/
/* main driver */
int main()
{
    /* Open the input data file and process its contents */
    //add multiple txt files each with their own case, or have all in one file
    if ((in_fp = fopen("..\\front.txt", "r")) == NULL) {
        printf("ERROR - cannot open front.txt \n");
    } else {
        getChar();
        do {
            lex();
        } while (nextToken != EOF);
        printf("Parsing complete!", "s");
    }

    return 0;
}

/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the
 * token */
int lookup(char ch) {
    switch (ch) {
        case '(':
            addChar();
            nextToken = LEFT_PAREN;
            break;
        case ')':
            addChar();
            nextToken = RIGHT_PAREN;
            break;
        case '+':
            addChar();
            nextToken = ADD_OP;
            break;
        case '-':
            addChar();
            nextToken = SUB_OP;
            break;
        case '*':
            addChar();
            nextToken = MULT_OP;
            break;
        case '/':
            addChar();
            nextToken = DIV_OP;
            break;
            //added code
        case '&':
            addChar();
            getChar();
            if(nextToken == '&'){
                addChar();
                nextToken = AND_OP;
                break;
            }else {
                break;
            }
        case '|': //dosen't read value as ||, but as |. what makes this the case?
            addChar();
            getChar();
            if(nextToken == '|'){
                addChar();
                nextToken = OR_OP;
                break;
            }else{
                break;
            }
        case '<':
            addChar();
            getChar();
            if(nextToken == '='){
                addChar();
                nextToken = LESSEQUAL_OP;
                break;
            }else{
                nextToken = LESS_OP;
                break;
            }
        case '>':
            addChar();
            getChar();
            if(nextToken == '='){
                addChar();
                nextToken = GREATEREQUAL_OP;
                break;
            }else{
                nextToken = GREATER_OP;
                break;
            }
        case '=':
            addChar();
            getChar();
            if(nextToken == '='){
                nextToken = EQUAL_OP;
                break;
            }else{
                nextToken = ASSIGN_OP;
                break;
            }
        case '!':
            addChar();
            getChar();
            if(nextToken == '='){
                nextToken = NOTEQUAL_OP;
                break;
            }else {
                break;
            }
        case '%':
            addChar();
            nextToken = MOD_OP;
            break;
        default:
            addChar();
            nextToken = EOF;
            break;
    }
    return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    } else {
        printf("Error - lexeme is too long \n");
    }
}

/*****************************************************/
/* getChar - a function to get the next character of input and determine its
 * character class */
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else charClass = UNKNOWN;
    } else {
        charClass = EOF;
    }
}

/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace
 * character */
void getNonBlank() {
    while (isspace(nextChar)) getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
        /* Parse identifiers */
        case LETTER:
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
            break;

        /* Parse integer literals */
        case DIGIT:
            addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();
                getChar();
            }
            while (charClass == LETTER) {
                addChar();
                getChar();
                if (charClass == UNKNOWN) {
                    // throw error
                    printf("ERROR: Invalid Token: '%s'. Parsing Terminated.", lexeme);
                    //break;
                    exit(0);
                }
            }

            nextToken = INT_LIT;
            break;

        /* Parentheses and operators */
        case UNKNOWN:
            lookup(nextChar);
            getChar();
            break;

        /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;
    } /* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
} /* End of function lex */
