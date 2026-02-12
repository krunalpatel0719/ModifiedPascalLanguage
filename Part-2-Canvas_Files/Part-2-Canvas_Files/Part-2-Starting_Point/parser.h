//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <set>
#include <iostream>

using namespace std;

// Holds the symbols in the interpreted program
extern set<string> symbolTable;

extern int nextToken;        // next token returned by lexer

extern "C" {
	// Instantiate global variables used by flex
	extern int   yylex();      // the generated lexical analyzer
	extern char* yytext;       // text of current lexeme
}

// Function declarations
void program();
void block();
void statement();
void assignment();
void compound();
void write();
void read();
void if_statement();
void while_statement();

void variable();

void expression();
void simple_expression();
void term();
void factor();



#endif /* PARSER_H */
