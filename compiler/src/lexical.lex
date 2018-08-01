%{

	#include <stdio.h>
	#include "token.h"
	int line   = 1; int column = 1;

%}

digit       [0-9]
letter		[a-zA-Z]
id	        {letter}([a-zA-Z0-9_]){0,30}	
hex         0[xX]{1}[0-9a-fA-F]+
real        [0-9]+\.[0-9]*
exp         [eE]\+[0-9]+
commentLine [/][/].*

%x BLOCK_COMMENT

%%

 /* Comment */
{commentLine}           { column = 1; }
[/][*]                  { column += yyleng; BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/"     { column += yyleng; BEGIN 0; }
<BLOCK_COMMENT>[^*\n]+  { column += yyleng; }
<BLOCK_COMMENT>"*"      { column += yyleng; }
<BLOCK_COMMENT>"\n"     { column = 1; line++; }

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
"null"				{ printf("%d %d %d %d %s\n", line, column, yyleng, tNull, yytext); column += yyleng; }

 /* Loops */

"for"             	{ printf("%d %d %d %d %s\n", line, column, yyleng, tFor, yytext); column += yyleng; }
"while"             { printf("%d %d %d %d %s\n", line, column, yyleng, tWhile, yytext); column += yyleng; }

 /* Control statements */

"if"             	{ printf("%d %d %d %d %s\n", line, column, yyleng, tIf, yytext); column += yyleng; }
"else"              { printf("%d %d %d %d %s\n", line, column, yyleng, tElse, yytext); column += yyleng; }

 /* Class patterns */

"class"             { printf("%d %d %d %d %s\n", line, column, yyleng, tClass, yytext); column += yyleng; }
"extends"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tExtends, yytext); column += yyleng; }
"this\."            { printf("%d %d %d %d %s\n", line, column, yyleng, tThis, yytext); column += yyleng; }
"\."            	{ printf("%d %d %d %d %s\n", line, column, yyleng, tDot, yytext); column += yyleng; }

 /* Interface patterns */

"interface"         { printf("%d %d %d %d %s\n", line, column, yyleng, tInterface, yytext); column += yyleng; }
"implements"     	{ printf("%d %d %d %d %s\n", line, column, yyleng, tImplements, yytext); column += yyleng; }

 /* Exit scope */

"break"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tBreak, yytext); column += yyleng; }
"return"     		{ printf("%d %d %d %d %s\n", line, column, yyleng, tReturn, yytext); column += yyleng; }

 /* IO */

"print"             { printf("%d %d %d %d %s\n", line, column, yyleng, tPrint, yytext); column += yyleng; }
"readLine"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tReadLine, yytext); column += yyleng; }
"readInteger"       { printf("%d %d %d %d %s\n", line, column, yyleng, tReadInteger, yytext); column += yyleng; }

 /* News  */

"new"         		{ printf("%d %d %d %d %s\n", line, column, yyleng, tNew, yytext); column += yyleng; }
"newArray"     		{ printf("%d %d %d %d %s\n", line, column, yyleng, tNewArray, yytext); column += yyleng; }

 /* Identifier */

{id}                { printf("%d %d %d %d %s\n", line, column, yyleng, tId, yytext); column += yyleng; }

 /*** Operators ***/
 /* Arithmetic */

"+"             { printf("%d %d %d %d %s\n", line, column, yyleng, tPlus, yytext); column += yyleng; }
"-"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tMinus, yytext); column += yyleng; }
"*"       		{ printf("%d %d %d %d %s\n", line, column, yyleng, tMulti, yytext); column += yyleng; }
"/"             { printf("%d %d %d %d %s\n", line, column, yyleng, tDiv, yytext); column += yyleng; }
"%"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tMod, yytext); column += yyleng; }

 /* Relational */

"<"             { printf("%d %d %d %d %s\n", line, column, yyleng, tLess, yytext); column += yyleng; }
"<="         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tLessEqual, yytext); column += yyleng; }
">"       		{ printf("%d %d %d %d %s\n", line, column, yyleng, tGreater, yytext); column += yyleng; }
">="            { printf("%d %d %d %d %s\n", line, column, yyleng, tGreaterEqual, yytext); column += yyleng; }
"="         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tAssignment, yytext); column += yyleng; }
"=="            { printf("%d %d %d %d %s\n", line, column, yyleng, tEqual, yytext); column += yyleng; }
"!="         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tDiff, yytext); column += yyleng; }

 /* Logic */

"&&"            { printf("%d %d %d %d %s\n", line, column, yyleng, tAnd, yytext); column += yyleng; }
"||"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tOr, yytext); column += yyleng; }
"!"       		{ printf("%d %d %d %d %s\n", line, column, yyleng, tNot, yytext); column += yyleng; }

 /* Symbols  */
";"             { printf("%d %d %d %d %s\n", line, column, yyleng, tSemiColon, yytext); column += yyleng; }
","         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tComma, yytext); column += yyleng; }
"["       		{ printf("%d %d %d %d %s\n", line, column, yyleng, tBracketLeft, yytext); column += yyleng; }
"]"            	{ printf("%d %d %d %d %s\n", line, column, yyleng, tBracketRight, yytext); column += yyleng; }
"("         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tParLeft, yytext); column += yyleng; }
")"            	{ printf("%d %d %d %d %s\n", line, column, yyleng, tParRight, yytext); column += yyleng; }
"{"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tBraceLeft, yytext); column += yyleng; }
"}"         	{ printf("%d %d %d %d %s\n", line, column, yyleng, tBraceRight, yytext); column += yyleng; }


 /* Lines */

[\t ]+              { column += yyleng; /* check whitespaces */ }
"\n"                { column = 1; line++; /* detect new line */ }

 /* Others */

.          ;
%%

