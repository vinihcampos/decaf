%option noyywrap
%option nounput
%{
    #include "token.h"
    #define ID_MAX_SZ 31

    int currRow = 1;
    int currColumn = 1;
    int row = 1;
    int column = 1;
    Token tok;
 
    void updateToken(Token token){
        row = currRow;
        column = currColumn;
        currColumn += yyleng;
        tok = token;
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
{commentLine}           { currColumn = 1; }
[/][*]                  { currColumn += yyleng; BEGIN(BLOCK_COMMENT); }
<BLOCK_COMMENT>"*/"     { currColumn += yyleng; BEGIN 0; }
<BLOCK_COMMENT>[^*\n]+  { currColumn += yyleng; }
<BLOCK_COMMENT>"*"      { currColumn += yyleng; }

 /* Constants */

{hex}|{digit}+  { updateToken(tIntConstant); return 0; }
\".*\"          { updateToken(tStringConstant); return 0; }
false           { updateToken(tFalse); return 0; }
true            { updateToken(tTrue); return 0; }
{real}{exp}*    { updateToken(tDoubleConstant); return 0; }
null            { updateToken(tNull); return 0; }

 /* Errors  */
{id}            {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
				        updateToken(tId); return 0; 
                    }else{
                        REJECT;
                    }
                }

{userType}      {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
                        updateToken(tUserType); return 0; 
                    }else{
                        REJECT;
                    }
                }

{notNumber}     { 
                    fprintf(stderr, "Error: the %s is not a valid number\n", yytext);
                    currColumn += yyleng;			
                }   
 
 /* Base types  */

void            { updateToken(tVoid); return 0; }
int             { updateToken(tInt); return 0; }
double          { updateToken(tDouble); return 0; }
bool            { updateToken(tBool); return 0; }
string          { updateToken(tString); return 0; }

 /* Loops */

for             { updateToken(tFor); return 0; }
while           { updateToken(tWhile); return 0; }

 /* Control statements */

if              { updateToken(tIf); return 0; }
else            { updateToken(tElse); return 0; }

 /* Class patterns */

class           { updateToken(tClass); return 0; }
extends         { updateToken(tExtends); return 0; }
this            { updateToken(tThis); return 0; }
"\."            { updateToken(tDot); return 0; }

 /* Interface patterns */

interface       { updateToken(tInterface); return 0; }
implements      { updateToken(tImplements); return 0; }

 /* Exit scope */

break           { updateToken(tBreak); return 0; }
return          { updateToken(tReturn); return 0; }

 /* IO */

print           { updateToken(tPrint); return 0; }
readLine        { updateToken(tReadLine); return 0; }
readInteger     { updateToken(tReadInteger); return 0; }

 /* News  */

new             { updateToken(tNew); return 0; }
newArray        { updateToken(tNewArray); return 0; }

 /* Identifier */

{id}            { updateToken(tId); return 0; }
{userType}      { updateToken(tUserType); return 0; }

 /*** Operators ***/
 /* Arithmetic */

"+"             { updateToken(tPlus); return 0; }
"-"             { updateToken(tMinus); return 0; }
"*"             { updateToken(tMulti); return 0; }
"/"             { updateToken(tDiv); return 0; }
"%"             { updateToken(tMod); return 0; }

 /* Relational */

"<"             { updateToken(tLess); return 0; }
"<="            { updateToken(tLessEqual); return 0; }
">"             { updateToken(tGreater); return 0; }
">="            { updateToken(tGreaterEqual); return 0; }
"="             { updateToken(tAssignment); return 0; }
"=="            { updateToken(tEqual); return 0; }
"!="            { updateToken(tDiff); return 0; }

 /* Logic */

"&&"            { updateToken(tAnd); return 0; }
"||"            { updateToken(tOr); return 0; }
"!"             { updateToken(tNot); return 0; }

 /* Symbols  */
";"             { updateToken(tSemiColon); return 0; }
","             { updateToken(tComma); return 0; }
"["             { updateToken(tBracketLeft); return 0; }
"]"             { updateToken(tBracketRight); return 0; }
"("             { updateToken(tParLeft); return 0; }
")"             { updateToken(tParRight); return 0; }
"{"             { updateToken(tBraceLeft); return 0; }
"}"             { updateToken(tBraceRight); return 0; }

 /* EOF */
 <<EOF>>        { updateToken(tEOF); return 0; yyterminate(); }


 /* Lines */

[\t ]+          { currColumn += yyleng; /* check whitespaces */ }
"\n"            { currColumn = 1; currRow++; /* detect new currRow */ }

 /* Errors  */

.               {   
                    fprintf(stderr, "Warning: the %s is not a recognized pattern\n", yytext); 
                    currColumn += yyleng;
                }
%%