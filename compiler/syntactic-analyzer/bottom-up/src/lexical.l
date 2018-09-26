%option noyywrap
%option nounput
%{  
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
{commentLine}           { column = 1; }
[/][*]                  { column += yyleng; BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/"     { column += yyleng; BEGIN 0; }
<BLOCK_COMMENT>[^*\n]+  { column += yyleng; }
<BLOCK_COMMENT>"*"      { column += yyleng; }

 /* Constants */

{hex}|{digit}+  { column += yyleng; yylval = strtol(yytext, 0, 10); return INTCONSTANT; }
\".*\"          { column += yyleng; yylval = strdup(yytext); return STRINGCONSTANT; }
false           { column += yyleng; return FALSE; }
true            { column += yyleng; return TRUE; }
{real}{exp}*    { column += yyleng; yylval = atof(yytext); return DOUBLECONSTANT; }
null            { column += yyleng; return TNULL; }

 /* Errors  */
{id}            {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
				        column += yyleng; yylval = strdup(yytext); return ID; 
                    }else{
                        REJECT;
                    }
                }

{userType}      {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
                        column += yyleng; yylval = strdup(yytext); return USERTYPE; 
                    }else{
                        REJECT;
                    }
                }

{notNumber}     { 
                    fprintf(stderr, "Error: the %s is not a valid number\n", yytext);
                    column += yyleng;			
                }   
 
 /* Base types  */

void            { column += yyleng; return VOID; }
int             { column += yyleng; return INT; }
double          { column += yyleng; return DOUBLE; }
bool            { column += yyleng; return BOOL; }
string          { column += yyleng; return STRING; }

 /* Loops */

for             { column += yyleng; return FOR; }
while           { column += yyleng; return WHILE; }

 /* Control statements */

if              { column += yyleng; return IF; }
else            { column += yyleng; return ELSE; }

 /* Class patterns */

class           { column += yyleng; return CLASS; }
extends         { column += yyleng; return EXTENDS; }
this            { column += yyleng; return THIS; }
"\."            { column += yyleng; return yytext[0]; }

 /* Interface patterns */

interface       { column += yyleng; return INTERFACE; }
implements      { column += yyleng; return IMPLEMENTS; }

 /* Exit scope */

break           { column += yyleng; return BREAK; }
return          { column += yyleng; return RETURN; }

 /* IO */

print           { column += yyleng; return PRINT; }
readLine        { column += yyleng; return READLINE; }
readInteger     { column += yyleng; return READINTEGER; }

 /* News  */

new             { column += yyleng; return NEW; }
newArray        { column += yyleng; return NEWARRAY; }

 /* Identifier */

{id}            { column += yyleng; yylval = strdup(yytext); return ID; }
{userType}      { column += yyleng; yylval = strdup(yytext); return USERTYPE; }

 /*** Operators ***/
 /* Arithmetic */

"+"             { column += yyleng; return yytext[0]; }
"-"             { column += yyleng; return yytext[0]; }
"*"             { column += yyleng; return yytext[0]; }
"/"             { column += yyleng; return yytext[0]; }
"%"             { column += yyleng; return yytext[0]; }

 /* Relational */

"<"             { column += yyleng; return L; }
"<="            { column += yyleng; return LEQ; }
">"             { column += yyleng; return G; }
">="            { column += yyleng; return GEQ; }
"="             { column += yyleng; return yytext[0]; }
"=="            { column += yyleng; return EQ; }
"!="            { column += yyleng; return NEQ; }

 /* Logic */

"&&"            { column += yyleng; return AND; }
"||"            { column += yyleng; return OR; }
"!"             { column += yyleng; return yytext[0]; }

 /* Symbols  */
";"             { column += yyleng; return yytext[0]; }
","             { column += yyleng; return yytext[0]; }
"["             { column += yyleng; return yytext[0]; }
"]"             { column += yyleng; return yytext[0]; }
"("             { column += yyleng; return yytext[0]; }
")"             { column += yyleng; return yytext[0]; }
"{"             { column += yyleng; return yytext[0]; }
"}"             { column += yyleng; return yytext[0]; }

 /* EOF */
 <<EOF>>        { column += yyleng; return EOF; yyterminate(); }


 /* Lines */

[\t ]+          { column += yyleng; /* check whitespaces */ }
"\n"            { column = 1; row++; /* detect new row */ }

 /* Errors  */

.               {   
                    fprintf(stderr, "Warning: the %s is not a recognized pattern\n", yytext); 
                    column += yyleng;
                }
%%