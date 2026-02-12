//**************************************************************************
 
// Replace with appropriate header comment......

//**************************************************************************

#include <stdio.h>
#include <iostream>
#include "lexer.h"
#include "parser.h"

using namespace std;

extern "C"
{
  extern int   yylex();      // the generated lexical analyzer
  extern char *yytext;       // text of current lexeme
}

int nextToken = 0;

// Production functions
bool firstOf_sentence();
bool noun_check();
bool verb_check();
bool adjective_check();

void noun();
void verb();
void adjective();

int noun_counter = 1;
int verb_counter = 1;
int adjective_counter = 1;

//*****************************************************************************
// Get the next lexeme (word in sentence)
int lex() {
  nextToken = yylex();
  if( nextToken == TOK_EOF ) {
    yytext[0] = 'E'; yytext[1] = 'O'; yytext[2] = 'F'; yytext[3] = 0;   
  }

  printf("Next token: %d, lexeme: |%s|\n", nextToken, yytext);
  return nextToken;
}
//*****************************************************************************
// Report what we found
void output( string what ) {
  cout << "===> Accepted " << what << ": |" << yytext << "| <===" << endl;
}
//*****************************************************************************
// <sentence> -> <noun phrase> <verb phrase> <noun phrase>
void sentence() 
{
  if( firstOf_sentence() == false )
    throw( "<sentence> did not start with an article or possessive." );

  cout << "Enter <sentence>" << endl;

  /* TODO: Add code here... */ 
  noun();
  verb();
  noun();
  cout << "Exit <sentence>" << endl;
} 
//*****************************************************************************
bool firstOf_sentence() {
  /* TODO: Finish this method... */
  if (nextToken == ARTICLE || nextToken == POSSESSIVE) {
    return true;
  }
  return false;
}



/*
    TODO: Add functions for the other grammar productions...
*/

void noun()
{
  int local_noun_counter = noun_counter;
  if( noun_check() == false )
    throw( "<noun phrase> did not start with an article or possessive." );

  cout << " Enter <noun phrase> " << local_noun_counter << endl;

  adjective();
  if (nextToken == NOUN) {
    output("NOUN");
    lex();
  }
  else {
    throw("<noun phrase> did not have a noun.");
  }
  cout << " Exit <noun phrase> " << local_noun_counter << endl;
}

bool noun_check() {
  if (nextToken == ARTICLE || nextToken == POSSESSIVE ) {
    noun_counter++;
    return true;
  }
  return false;
}

void adjective() 
{ 
  int local_adjective_counter = adjective_counter;
  if( adjective_check() == false )
      throw( "<adjective phrase> did not start with an article or possessive." );

    cout << " Enter <adjective phrase> " << local_adjective_counter << endl;

   
    if( nextToken == ARTICLE) {
      output("ARTICLE");
      lex();
      if (nextToken == ADJECTIVE) {
        output("ADJECTIVE");
        lex();
      }
      else {
        throw("<adjective phrase> did not have an adjective.");
      }
    }
    else if (nextToken == POSSESSIVE) {
      output("POSSESSIVE");
      lex();
      if (nextToken == ADJECTIVE) {
        output("ADJECTIVE");
        lex();
      }
      else {
        throw("<adjective phrase> did not have an adjective.");
      }
    }
    else {
      throw("<adjective phrase> did not start with an article or possessive.");
    }


    cout << " Exit <adjective phrase> " << local_adjective_counter << endl;
}

bool adjective_check() {
  if (nextToken == ARTICLE || nextToken == POSSESSIVE ) {
      adjective_counter++;
      return true;
    }
    return false;
}

void verb() {
  int local_verb_counter = verb_counter;
  if(verb_check() == false )
      throw( "<verb phrase> did not start with an verb or an adverb.");

    cout << " Enter <verb phrase> " << local_verb_counter << endl;

   
    if( nextToken == VERB) {
      output("VERB");
      lex();
    
    }
    else if (nextToken == ADVERB) {
      output("ADVERB");
      lex();
      verb();
    }
    else {
      throw("<verb phrase> did not start with an verb or an adverb.");
    }


    cout << " Exit <verb phrase> " << local_verb_counter << endl;
}

bool verb_check() {
  if (nextToken == VERB || nextToken == ADVERB ) {
    verb_counter++;
    return true;
  }
  return false;

}