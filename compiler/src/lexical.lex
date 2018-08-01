%{

	#include <stdio.h>
	#include "token.h"
	int line   = 1; int column = 1;

%}

digit       [0-9]
letter		[a-zA-Z]
id	        {letter}+[a-zA-Z0-9_]*	
hex         0[xX]{1}[0-9a-fA-F]+
real        [0-9]+\.[0-9]*
exp         [eE]\+[0-9]+

%%

 /* Base types  */

"void"              { printf("%d %d %d %d %s\n", line, column, yyleng, tVoid, yytext); column += yyleng; }
"int"               { printf("%d %d %d %d %s\n", line, column, yyleng, tInt, yytext); column += yyleng; }
"double"            { printf("%d %d %d %d %s\n", line, column, yyleng, tDouble, yytext); column += yyleng; }
"bool"              { printf("%d %d %d %d %s\n", line, column, yyleng, tBool, yytext); column += yyleng; }
"string"            { printf("%d %d %d %d %s\n", line, column, yyleng, tString, yytext); column += yyleng; }

 /* Constants */

{real}{exp}*        { printf("%d %d %d %d %s\n", line, column, yyleng, tDoubleConstant, yytext); column += yyleng; }
{hex}|{digit}+      { printf("%d %d %d %d %s\n", line, column, yyleng, tIntConstant, yytext); column += yyleng; }
\".*\"              { printf("%d %d %d %d %s\n", line, column, yyleng, tStringConstant, yytext); column += yyleng; }
"false"             { printf("%d %d %d %d %s\n", line, column, yyleng, tFalse, yytext); column += yyleng; }
"true"              { printf("%d %d %d %d %s\n", line, column, yyleng, tTrue, yytext); column += yyleng; }

 /* Loops */
 /* Control statements */
 
 /* Identifier */

{id}                { printf("%d %d %d %d %s\n", line, column, yyleng, tId, yytext); column += yyleng; }

 /* Lines */

[\t ]+              { column++; /* check whitespaces */ }
"\n"                { column = 1; line++; /* detect new line */ }

 /* Others */

.          ;
%%

