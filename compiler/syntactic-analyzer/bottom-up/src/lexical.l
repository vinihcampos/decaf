%option noyywrap
%option nounput
%{  
    // Including AST files
    #include "declaration.h"
    #include "type.h"
    #include "declaration_variable.h"
    #include "declaration_function.h"
    #include "declaration_class.h"
    #include "declaration_interface.h"
    #include "declaration_variable_list.h"
    #include "formal.h"
    #include "field.h"
    #include "prototype.h"
    #include "stmt_block.h"
    #include "stmt.h"
    #include "type.h"
    #include "expression.h"
    #include "operator_assignment.h"
    #include "lvalue.h"
    #include "call.h"
    #include "constant.h"
    #include "stmt_print.h"
    #include "stmt_return.h"
    #include "stmt_break.h"
    #include "stmt_if.h"
    #include "stmt_while.h"
    #include "stmt_for.h"

    // Remaining include
    #include "y.tab.h"
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #define ID_MAX_SZ 31

    int row = 1;
    int column = 1;
%}

digit       [0-9]
letter      [a-zA-Z]
lowerCase   [a-z]
upperCase   [A-Z]
hexLetter   [a-fA-F]
id          {lowerCase}({letter}|{digit}|[_])*
userType    {upperCase}({letter}|{digit}|[_])*	
notNumber   {digit}+{id}
hex         0[xX]({digit}|{hexLetter})+
real        {digit}+\.{digit}*
exp         [eE]([+]){0,1}{digit}+
commentLine [/][/].*

%x BLOCK_COMMENT

%%

 /* Comment */
{commentLine}           { yylval.lexeme = strdup(yytext); column = 1; }
[/][*]                  { yylval.lexeme = strdup(yytext); column += yyleng; BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/"     { yylval.lexeme = strdup(yytext); column += yyleng; BEGIN 0; }
<BLOCK_COMMENT>[^*\n]+  { yylval.lexeme = strdup(yytext); column += yyleng; }
<BLOCK_COMMENT>"*"      { yylval.lexeme = strdup(yytext); column += yyleng; }

 /* Constants */

{hex}|{digit}+  { yylval.lexeme = strdup(yytext); column += yyleng; return INTCONSTANT; }
\".*\"          { yylval.lexeme = strdup(yytext); column += yyleng; return STRINGCONSTANT; }
false           { yylval.lexeme = strdup(yytext); column += yyleng; return FALSE; }
true            { yylval.lexeme = strdup(yytext); column += yyleng; return TRUE; }
{real}{exp}*    { yylval.lexeme = strdup(yytext); column += yyleng; return DOUBLECONSTANT; }
null            { yylval.lexeme = strdup(yytext); column += yyleng; return TNULL; }

 /* Errors  */
{id}            {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
				        yylval.lexeme = strdup(yytext); column += yyleng; return ID; 
                    }else{
                        REJECT;
                    }
                }

{userType}      {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
                        yylval.lexeme = strdup(yytext); column += yyleng; return USERTYPE; 
                    }else{
                        REJECT;
                    }
                }

{notNumber}     { 
                    fprintf(stderr, "Error: the %s is not a valid number\n", yytext);
                    column += yyleng;			
                }   
 
 /* Base types  */

void            { yylval.lexeme = strdup(yytext); column += yyleng; return VOID; }
int             { yylval.lexeme = strdup(yytext); column += yyleng; return INT; }
double          { yylval.lexeme = strdup(yytext); column += yyleng; return DOUBLE; }
bool            { yylval.lexeme = strdup(yytext); column += yyleng; return BOOL; }
string          { yylval.lexeme = strdup(yytext); column += yyleng; return STRING; }

 /* Loops */

for             { yylval.lexeme = strdup(yytext); column += yyleng; return FOR; }
while           { yylval.lexeme = strdup(yytext); column += yyleng; return WHILE; }

 /* Control statements */

if              { yylval.lexeme = strdup(yytext); column += yyleng; return IF; }
else            { yylval.lexeme = strdup(yytext); column += yyleng; return ELSE; }

 /* Class patterns */

class           { yylval.lexeme = strdup(yytext); column += yyleng; return CLASS; }
extends         { yylval.lexeme = strdup(yytext); column += yyleng; return EXTENDS; }
this            { yylval.lexeme = strdup(yytext); column += yyleng; return THIS; }
"\."            { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }

 /* Interface patterns */

interface       { yylval.lexeme = strdup(yytext); column += yyleng; return INTERFACE; }
implements      { yylval.lexeme = strdup(yytext); column += yyleng; return IMPLEMENTS; }

 /* Exit scope */

break           { yylval.lexeme = strdup(yytext); column += yyleng; return BREAK; }
return          { yylval.lexeme = strdup(yytext); column += yyleng; return RETURN; }

 /* IO */

print           { yylval.lexeme = strdup(yytext); column += yyleng; return PRINT; }
readLine        { yylval.lexeme = strdup(yytext); column += yyleng; return READLINE; }
readInteger     { yylval.lexeme = strdup(yytext); column += yyleng; return READINTEGER; }

 /* News  */

new             { yylval.lexeme = strdup(yytext); column += yyleng; return NEW; }
newArray        { yylval.lexeme = strdup(yytext); column += yyleng; return NEWARRAY; }

 /* Identifier */

{id}            { yylval.lexeme = strdup(yytext); column += yyleng; return ID; }
{userType}      { yylval.lexeme = strdup(yytext); column += yyleng; return USERTYPE; }

 /*** Operators ***/
 /* Arithmetic */

"+"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"-"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"*"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"/"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"%"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }

 /* Relational */

"<"             { yylval.lexeme = strdup(yytext); column += yyleng; return L; }
"<="            { yylval.lexeme = strdup(yytext); column += yyleng; return LEQ; }
">"             { yylval.lexeme = strdup(yytext); column += yyleng; return G; }
">="            { yylval.lexeme = strdup(yytext); column += yyleng; return GEQ; }
"="             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"=="            { yylval.lexeme = strdup(yytext); column += yyleng; return EQ; }
"!="            { yylval.lexeme = strdup(yytext); column += yyleng; return NEQ; }

 /* Logic */

"&&"            { yylval.lexeme = strdup(yytext); column += yyleng; return AND; }
"||"            { yylval.lexeme = strdup(yytext); column += yyleng; return OR; }
"!"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }

 /* Symbols  */
";"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
","             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"["             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"]"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"("             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
")"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"{"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }
"}"             { yylval.lexeme = strdup(yytext); column += yyleng; return yytext[0]; }

 /* EOF */
 <<EOF>>        { yylval.lexeme = strdup(yytext); column += yyleng; return EOF; yyterminate(); }


 /* Lines */

[\t ]+          { column += yyleng; /* check whitespaces */ }
"\n"            { column = 1; row++; /* detect new row */ }

 /* Errors  */

.               {   
                    fprintf(stderr, "Warning: the %s is not a recognized pattern\n", yytext); 
                    column += yyleng;
                }
%%