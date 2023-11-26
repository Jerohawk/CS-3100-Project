/**
 * This the example lexical analyzer code in pages 173 - 177 of the
 * textbook,
 *
 * Sebesta, R. W. (2012). Concepts of Programming Languages.
 * Pearson, 10th edition.
 *
 */
//create string array, then compare identifiers with the array members(define global array, to see all key words)
//library function string compare
//use while/for loop to do comparison
//output is good, task 2 done! BUT YOU NNEED TO EXPLAIN THE WHY
/**
Andrew, im not sure that you put the right code into the merged project, which would explain the werid formating, as
 * im not seeing my updated code from that one class. I'll resend this project into the github for reformating.
 * Let me know when you get it merged again, i want to make sure my code from my laptop is there (use this one)
 * -Peter B.
 */

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <string.h>
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
#define NOT_OP 31
//Bonus points operators
#define FOR_CODE 50
#define IF_CODE 51
#define ELSE_CODE 52
#define WHILE_CODE 53
#define DO_CODE 54
#define SWITCH_CODE 55
#define INT_CODE 56
#define FLOAT_CODE 57
#define PRINT_CODE 58


/******************************************************/
/* main driver */
int main()
{
    /* Open the input data file and process its contents */
    //add multiple txt files each with their own case, or have all in one file
    if ((in_fp = fopen("..\\front4.txt", "r")) == NULL) {
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
        case 'for':
            addChar();
            nextToken = FOR_CODE;
            break;
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
            nextToken = AND_OP;
            break;
        case '|':
            addChar();
            nextToken = OR_OP;
            break;
        case '=':
            addChar();
            nextToken = ASSIGN_OP;
            //printf("first equal sign \n");
            break;
        case '!':
            addChar();
            nextToken = NOT_OP;
            break;
        case '<':
            addChar();
            nextToken = LESS_OP;
            break;
        case '>':
            addChar();
            nextToken = GREATER_OP;
            break;
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

/****************************************************/
//attempt 2 bonus points
//lookup table for reserved words
int reserved(char word[]){
    if(strcmp(word,"for") == 0)
        nextToken = FOR_CODE;
        //printf("print correct lexeme");
    else if(strcmp(word,"if") == 0)
        nextToken = IF_CODE;
    else if(strcmp(word,"else") == 0)
        nextToken = ELSE_CODE;
    else if(strcmp(word,"while") == 0)
        nextToken = WHILE_CODE;
    else if(strcmp(word,"do") == 0)
        nextToken = DO_CODE;
    else if(strcmp(word,"switch") == 0)
        nextToken = SWITCH_CODE;
    else if(strcmp(word,"int") == 0)
        nextToken = INT_CODE;
    else if(strcmp(word,"float") == 0)
        nextToken = FLOAT_CODE;
    else if(strcmp(word,"print") == 0)
        nextToken = PRINT_CODE;
    else
        nextToken = IDENT;
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
            //nextToken = IDENT;
            nextToken = reserved(lexeme);
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
            switch (nextToken) {
                case (AND_OP):
                    if (nextChar == '&') {
                        addChar();
                        getChar();
                    } else {
                        nextToken = -1;
                    }
                    break;
                case (OR_OP):
                    if (nextChar == '|') {
                        addChar();
                        getChar();
                    } else {
                        nextToken = -1;
                    }break;
                case (ASSIGN_OP):
                    if(nextChar == '='){
                        addChar();
                        nextToken = EQUAL_OP;
                        getChar();
                        //printf("second equal sign \n");
                    }
                    break;
                case (NOT_OP):
                    if(nextChar == '='){
                        addChar();
                        nextToken = NOTEQUAL_OP;
                        getChar();
                    }
                    break;
                case (LESS_OP):
                    if(nextChar == '='){
                        addChar();
                        nextToken = LESSEQUAL_OP;
                        getChar();
                    }
                    break;
                case (GREATER_OP):
                    if(nextChar == '='){
                        addChar();
                        nextToken = GREATEREQUAL_OP;
                        getChar();
                    }
                    break;
            }
            break;

            /* EOF */
        case EOF:
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = 0;
            break;

    }/* End of switch */
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
} /* End of function lex */
