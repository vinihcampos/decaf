/*** Definition ***/

%{
#include <stdio.h>
#include "token.h"
%}

%%
 /*** Rules ***/

[0-9]+  { printf("Saw an integer: %s\n", yytext); }

.|\n    { /* Ignore all other characters. */ }

%%

int main(void)
{
    yylex();
    return 0;
}
