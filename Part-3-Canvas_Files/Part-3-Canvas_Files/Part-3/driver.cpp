//*****************************************************************************
// purpose: Driver for Project Part 2 (parser for TIPS)
// Name: Krunal Patel
// NetId: krp356
// Purpose: Parsing Cpp file
// version: Fall 2022
//*****************************************************************************
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "parse_tree_nodes.h"
#include <cstring>


using namespace std;

extern "C" {
    // Instantiate global variables
    extern FILE *yyin;     // input stream
    extern FILE *yyout;    // output stream
    extern int   yyleng;   // length of current lexeme
    extern char *yytext;   // text of current lexeme
    extern int   yylineno; // line number for current lexeme
    extern int   yylex();  // the generated lexical analyzer
     extern int   yylex_destroy(); // deletes memory allocated by yylex
}

// Needed global variables
extern int nextToken; // token returned from yylex

//*****************************************************************************
// The main processing loop
//
int main(int argc, char* argv[]) {
    bool printParse = false;
    bool printTree = true; // whether to print the parse tree

    // Process any command-line switches
    for(int i = 1; i < argc; i++) {
        // -p flag: if requested, print while parsing
        if(strcmp(argv[i], "-p") == 0) {
        printParse = true;
        }
        // -t flag: if requested, print parse tree
        if(strcmp(argv[i], "-t") == 0) {
        printTree = true;
        }
        // -d flag: if requested, print while deleting parse tree
        if(strcmp(argv[i], "-d") == 0) {
        printDelete = true;
        }
    }
    
    // Set the input stream
    if (argc > 1) {
        printf("INFO: Using the %s file for input\n", argv[1]);
        yyin = fopen(argv[1], "r"); 
    }
    else {
        printf("INFO: Using the sample.pas file for input\n");
        yyin = fopen("sample.pas", "r");
    }
  
    if (!yyin) {
        printf("ERROR: input file not found\n");
        return EXIT_FAILURE;
    }

    // Set the output stream
    yyout = stdout;

    // Get the first token
    nextToken = yylex();

    // ExprNode* root = nullptr;
    ProgramNode* root = nullptr;

    // Fire up the parser!
    try {
        // Process the expected production
        root = program();  
        // expression(); // Build bottom-up to <expression>
        // program();
        lex();
        
        if (nextToken != TOK_EOF)
            throw "end of file expected, but there is more here!";
        
    } catch (char const *errmsg) {
        cout << endl << "***ERROR:" << endl;
        cout << "On line number " << yylineno << ", near |" << yytext << "|, error type ";
        cout << errmsg << endl;
        return EXIT_FAILURE;
    }
    
    // Tell the world about our success!!
    cout << endl << "=== GO BULLDOGS! Your parse was successful! ===" << endl;
    
    if (yyin)
        fclose(yyin);
        
    yylex_destroy();

    if(printTree) {
        cout << endl << "*** Print the Tree ***" << endl;
        cout << *root << endl << endl;
    }
    

    // Print out the symbol table
    cout << endl << "*** User Defined Symbols ***" << endl;
    set<string>::iterator it;
    for (it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        cout << *it << endl;
    }

    
    cout << endl << "*** Delete the Tree ***" << endl;
    delete root;
    root = nullptr;
   
    return EXIT_SUCCESS;
}

