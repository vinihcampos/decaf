%option noyywrap
%option nounput
%{
    #include "token.h"
    #define ID_MAX_SZ 31

    int row = 1;
    int column = 1;
 
    Token returnToken(Token token){
        column += yyleng;
        return token;
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

{hex}|{digit}+  { returnToken(tIntConstant); }
\".*\"          { returnToken(tStringConstant); }
false           { returnToken(tFalse); }
true            { returnToken(tTrue); }
{real}{exp}*    { returnToken(tDoubleConstant); }
null            { returnToken(tNull); }

 /* Errors  */
{id}            {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
				        returnToken(tId); 
                    }else{
                        REJECT;
                    }
                }

{userType}      {   
                    if(yyleng > ID_MAX_SZ){
                        fprintf(stderr, "Warning: the %s will be truncated, because it exceeded maximum size of an identifier\n", yytext);
                        returnToken(tUserType); 
                    }else{
                        REJECT;
                    }
                }

{notNumber}     { 
                    fprintf(stderr, "Error: the %s is not a valid number\n", yytext);
                    column += yyleng;			
                }   
 
 /* Base types  */

void            { returnToken(tVoid); }
int             { returnToken(tInt); }
double          { returnToken(tDouble); }
bool            { returnToken(tBool); }
string          { returnToken(tString); }

 /* Loops */

for             { returnToken(tFor); }
while           { returnToken(tWhile); }

 /* Control statements */

if              { returnToken(tIf); }
else            { returnToken(tElse); }

 /* Class patterns */

class           { returnToken(tClass); }
extends         { returnToken(tExtends); }
this            { returnToken(tThis); }
"\."            { returnToken(tDot); }

 /* Interface patterns */

interface       { returnToken(tInterface); }
implements      { returnToken(tImplements); }

 /* Exit scope */

break           { returnToken(tBreak); }
return          { returnToken(tReturn); }

 /* IO */

print           { returnToken(tPrint); }
readLine        { returnToken(tReadLine); }
readInteger     { returnToken(tReadInteger); }

 /* News  */

new             { returnToken(tNew); }
newArray        { returnToken(tNewArray); }

 /* Identifier */

{id}            { returnToken(tId); }
{userType}      { returnToken(tUserType); }

 /*** Operators ***/
 /* Arithmetic */

"+"             { returnToken(tPlus); }
"-"             { returnToken(tMinus); }
"*"             { returnToken(tMulti); }
"/"             { returnToken(tDiv); }
"%"             { returnToken(tMod); }

 /* Relational */

"<"             { returnToken(tLess); }
"<="            { returnToken(tLessEqual); }
">"             { returnToken(tGreater); }
">="            { returnToken(tGreaterEqual); }
"="             { returnToken(tAssignment); }
"=="            { returnToken(tEqual); }
"!="            { returnToken(tDiff); }

 /* Logic */

"&&"            { returnToken(tAnd); }
"||"            { returnToken(tOr); }
"!"             { returnToken(tNot); }

 /* Symbols  */
";"             { returnToken(tSemiColon); }
","             { returnToken(tComma); }
"["             { returnToken(tBracketLeft); }
"]"             { returnToken(tBracketRight); }
"("             { returnToken(tParLeft); }
")"             { returnToken(tParRight); }
"{"             { returnToken(tBraceLeft); }
"}"             { returnToken(tBraceRight); }

 /* EOF */
 <<EOF>>        { returnToken(tEOF); yyterminate(); }


 /* Lines */

[\t ]+          { column += yyleng; /* check whitespaces */ }
"\n"            { column = 1; row++; /* detect new row */ }

 /* Errors  */

.               {   
                    fprintf(stderr, "Warning: the %s is not a recognized pattern\n", yytext); 
                    column += yyleng;
                }
%%