%{

    #include <stdio.h>
    #include "token.h"
    #define ID_MAX_SZ 31
    
    int line = 1; 
    int column = 1;    
    int output = 0;    
 
    void printToken(int token){
        int len = yyleng;
        char * tokenStr = getTokenString(token);
        char * text;
        if((token == tId || token == tUserType) && len > 31){
            text = (char*) malloc(32);
            for(len = 0; len < 31; ++len) text[len] = yytext[len];
            text[31] = '\0';
        }else{
            text = yytext;
        }
        
        if(output) fprintf(yyout ,"%4d %6d %6d %14s %4d %s\n", line, column, len, tokenStr, token, text);
        else       printf("%4d %6d %6d %14s %4d %s\n", line, column, len, tokenStr, token, text);
        
        column += yyleng;
    }
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

{hex}|{digit}+  { printToken(tIntConstant); }
\".*\"          { printToken(tStringConstant); }
false           { printToken(tFalse); }
true            { printToken(tTrue); }
{real}{exp}*    { printToken(tDoubleConstant); }
null            { printToken(tNull); }

 /* Errors  */
{id}            {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
				        printToken(tId); 
                    }else{
                        REJECT;
                    }
                }

{userType}      {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
                        printToken(tUserType); 
                    }else{
                        REJECT;
                    }
                }

{notNumber}     { 
                    fprintf(stderr, "Error: the %s is not a valid number\n", yytext);
                    column += yyleng;			
                }   
 
 /* Base types  */

void            { printToken(tVoid); }
int             { printToken(tInt); }
double          { printToken(tDouble); }
bool            { printToken(tBool); }
string          { printToken(tString); }

 /* Loops */

for             { printToken(tFor); }
while           { printToken(tWhile); }

 /* Control statements */

if              { printToken(tIf); }
else            { printToken(tElse); }

 /* Class patterns */

class           { printToken(tClass); }
extends         { printToken(tExtends); }
this            { printToken(tThis); }
"\."            { printToken(tDot); }

 /* Interface patterns */

interface       { printToken(tInterface); }
implements      { printToken(tImplements); }

 /* Exit scope */

break           { printToken(tBreak); }
return          { printToken(tReturn); }

 /* IO */

print           { printToken(tPrint); }
readLine        { printToken(tReadLine); }
readInteger     { printToken(tReadInteger); }

 /* News  */

new             { printToken(tNew); }
newArray        { printToken(tNewArray); }

 /* Identifier */

{id}            { printToken(tId); }
{userType}      { printToken(tUserType); }

 /*** Operators ***/
 /* Arithmetic */

"+"             { printToken(tPlus); }
"-"             { printToken(tMinus); }
"*"             { printToken(tMulti); }
"/"             { printToken(tDiv); }
"%"             { printToken(tMod); }

 /* Relational */

"<"             { printToken(tLess); }
"<="            { printToken(tLessEqual); }
">"             { printToken(tGreater); }
">="            { printToken(tGreaterEqual); }
"="             { printToken(tAssignment); }
"=="            { printToken(tEqual); }
"!="            { printToken(tDiff); }

 /* Logic */

"&&"            { printToken(tAnd); }
"||"            { printToken(tOr); }
"!"             { printToken(tNot); }

 /* Symbols  */
";"             { printToken(tSemiColon); }
","             { printToken(tComma); }
"["             { printToken(tBracketLeft); }
"]"             { printToken(tBracketRight); }
"("             { printToken(tParLeft); }
")"             { printToken(tParRight); }
"{"             { printToken(tBraceLeft); }
"}"             { printToken(tBraceRight); }

 /* EOF */
 <<EOF>>        { printToken(tEOF); yyterminate(); }


 /* Lines */

[\t ]+          { column += yyleng; /* check whitespaces */ }
"\n"            { column = 1; line++; /* detect new line */ }

 /* Errors  */

.               {   
                    fprintf(stderr, "Warning: the %s is not a recognized pattern\n", yytext); 
                    column += yyleng;
                }
%%

int main(int argn, char * argv[]){
    if(argn > 1){
        yyin = fopen(argv[1], "r");
        if(argn > 2){
            yyout = fopen(argv[2], "w");
            output = 1;
            fprintf(yyout, "%4s %6s %6s %14s %4s %s\n", "Line", "Column", "Length", "Token", "Code", "Lexema");
        }else{
            printf("%4s %6s %6s %14s %4s %s\n", "Line", "Column", "Length", "Token", "Code", "Lexema");
        }

        yylex();
        
        fclose(yyin);
        fclose(yyout);
    }else{
        fprintf(stderr, "ERROR: There is no file to analyze!\n");
    }
    return 0;
}

