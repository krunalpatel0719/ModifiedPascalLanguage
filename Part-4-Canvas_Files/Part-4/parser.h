//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "parse_tree_nodes.h"
#include <string>
#include <stdlib.h>
#include <set>
#include <map>
#include <iostream>

using namespace std;

// Holds the symbols in the interpreted program

typedef map<string, float> symbolTableT; 
extern symbolTableT symbolTable; 

extern int nextToken;        // next token returned by lexer

extern "C" {
	// Instantiate global variables used by flex
	extern FILE *yyin;       // input stream
	extern int   yylex();      // the generated lexical analyzer
	extern char* yytext;       // text of current lexeme
}

extern int nextToken;        // next token returned by lexer
extern bool printParse; 
     // shall tree be printed while parsing?


/* Function declarations */
int lex();  

// Function declarations
ProgramNode* program();
BlockNode* block();
StatementNode* statement();
AssignmentStatementNode* assignment();
CompoundStatementNode* compound();
WriteStatementNode* write();
ReadStatementNode* read();
IfStatementNode* if_statement();
WhileStatementNode* while_statement();

void variable();

ExprNode* expression();
SimpleExprNode* simple_expression();
TermNode* term();
FactorNode* factor();

#define EPSILON 0.001 

static bool truth(float F) { 
  return !((EPSILON > F) && (F > -EPSILON)); 
} 
 

#endif /* PARSER_H */
