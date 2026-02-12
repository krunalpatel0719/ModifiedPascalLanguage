 /*********************************************************************
  Name: Krunal Patel              NetID: krp356
  Course: CSE 4714              
  Lab: 01 - Lexical Analyzer 
  Purpose of File: Contains the ....


 This is the file that you should modify for Lab 1.
 **********************************************************************/

%option noyywrap
%{
#include "lexer.h"

// global variable to hold current line number being read
int line_number = 1;
%}


%%

 /* Punctuation */

[,] {return SEPARATOR;}

 /* Generic Data values */

[0-9]{4}\/[0-9]{2}\/[0-9]{2} {return DATE;}
[yY]es {return YES;}
[nN]o {return NO;}
[Uu]nknown {return UNKNOWN_VALUE;}
[mM]issing {return MISSING;}
  
 /* Data Values */
 
[lL]aboratory\-[cC]onfirmed\ [cC]ase {return LABORATORY;}
[pP]robable\ [cC]ase {return PROBABLE;}
[mM]ale {return MALE;}
[fF]emale {return FEMALE;}
[oO]ther {return OTHER;}
[0]\ \-\ [9]\ [yY]ears {return AGE_0X;}
[1][0]\ \-\ [1][9]\ [yY]ears {return AGE_1X;}
[2][0]\ \-\ [3][9]\ [yY]ears {return AGE_2X;}
[4][0]\ \-\ [4][9]\ [yY]ears {return AGE_4X;}
[5][0]\ \-\ [5][9]\ [yY]ears  {return AGE_5X;}
[6][0]\ \-\ [6][9]\ [yY]ears {return AGE_6X;}
[7][0]\ \-\ [7][9]\ [yY]ears {return AGE_7X;}
[8][0]\+\ [yY]ears {return AGE_8X;}
\"[hH]ispanic\/[lL]atino\" {return HISPANIC;}
\"[aA]merican\ [iI]ndian\ \/\ [aA]laska\ [nN]ative\,\ [nN]on\-[hH]ispanic\" {return NATIVE_AMERICAN;}
\"[aA]sian\,\ [nN]on\-[hH]ispanic\" {return ASIAN;}
\"[bB]lack\,\ [nN]on\-[hH]ispanic\" {return BLACK;}
\"[nN]ative\ [hH]awaiian\ \/\ [oO]ther\ [pP]acific\ [iI]slander\,\ [nN]on\-[hH]ispanic\" {return PACIFIC_ISLANDER;}
\"[wW]hite\,\ [nN]on\-[hH]ispanic\" {return WHITE;}
\"[mM]ultiple\/[oO]ther\,\ [nN]on\-[hH]ispanic\" {return MULTIPLE_OTHER;}


\n {++line_number;}

 /* Eat any whitespace, will need to be modified to count lines */
 
[ \t\r]+   {}          /* nop */


 /* Found an unknown character */

.         { return UNKNOWN_TOKEN; }

 /* Recognize end of file */

<<EOF>>   { return EOF_TOKEN; }


