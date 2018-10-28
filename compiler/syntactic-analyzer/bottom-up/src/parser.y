%{
	#include <cstdio>
	#include "program.h"
	extern int yylval;
	extern int row, column;
	extern FILE* yyin;
	int yylex();
	void yyerror(char *);
	extern FILE* yyin;
	int error_found = 0;

%}
%token VOID INT DOUBLE BOOL STRING CLASS INTERFACE TNULL THIS EXTENDS IMPLEMENTS FOR WHILE IF ELSE RETURN BREAK NEW NEWARRAY PRINT READINTEGER READLINE ID USERTYPE INTCONSTANT DOUBLECONSTANT TRUE FALSE STRINGCONSTANT UMINUS L LEQ G GEQ EQ NEQ AND OR

%start program

%right '='
%left OR AND
%left L LEQ G GEQ EQ NEQ
%left '+' '-'
%left '*' '/' '%'
%right '!' UMINUS
%left ')'
%nonassoc '['
%left '.'
%%

program:	decl program
	|		%empty
	;

decl:	variableDecl
	|	functionDecl
	|	classDecl
	|	interfaceDecl
	|	error
	;

variableDecl:	variable ';'
	;

variableDeclList:	variableDecl variableDeclList
	|				%empty
	;

variable:	type ID
	;

type:	INT
	|	DOUBLE
	|	BOOL
	|	STRING
	|	USERTYPE
	|	type '[' ']'
	;

functionDecl:	type ID '(' formals ')' stmtBlock
	|			VOID ID '(' formals ')' stmtBlock
	;

formals:	variable formals1
	|		%empty
	;

formals1:	',' variable formals1
	|		%empty
	;

classDecl:	CLASS USERTYPE extends implements '{' field '}'
	;

extends:	EXTENDS USERTYPE
	|		%empty
	;

implements:	IMPLEMENTS USERTYPE implements1
	|		%empty
	;

implements1:	',' USERTYPE implements1
	|			%empty
	;

field:	variableDecl field
	|	functionDecl field
	|	%empty
	;

interfaceDecl:	INTERFACE USERTYPE '{' prototype '}'
	;

prototype:	type ID '(' formals ')' ';' prototype
	|		VOID ID '(' formals ')' ';' prototype
	|		%empty
	;

stmtBlock:	'{' variableDeclList stmtList '}'
	;

stmt:	expr1 ';'
	|	ifStmt
	|	whileStmt
	|	forStmt
	|	breakStmt
	|	returnStmt
	|	printStmt
	|	stmtBlock
	|	error
	;

stmtList:	stmt stmtList
	|		%empty
	;

ifStmt:	IF '(' expr ')' stmt
	|	IF '(' expr ')' stmt ELSE stmt
	;

whileStmt:	WHILE '(' expr ')' stmt
	;

forStmt:	FOR '(' expr1 ';' expr ';' expr1 ')' stmt
	;

returnStmt:	RETURN expr1 ';'
	;

breakStmt:	BREAK ';'
	;

printStmt:	PRINT '(' exprList ')' ';'
	;

expr:	lValue '=' expr
	|	constant
	|	lValue
	|	THIS
	|	call
	|	'(' expr ')'
	|	expr '+' expr
	|	expr '-' expr
	|	expr '*' expr
	|	expr '/' expr
	|	expr '%' expr
	|	'-' expr %prec UMINUS
	|	expr L expr
	|	expr LEQ expr
	|	expr G expr
	|	expr GEQ expr
	|	expr EQ expr
	|	expr NEQ expr
	|	expr AND expr
	|	expr OR expr
	|	'!' expr
	|	READINTEGER '(' ')'
	|	READLINE '(' ')'
	|	NEW '(' USERTYPE ')'
	|	NEWARRAY '(' expr ',' type ')'
	;

exprList:	expr exprList1
	|		%empty
	;

exprList1:	',' expr exprList1
	|		%empty
	;

expr1:	expr
	|	%empty
	;

lValue:	ID
	|	expr '.' ID
	|	expr '[' expr ']'
	;

call:	ID '(' exprList ')'
	|	expr '.' ID '(' exprList ')'
	;

constant:	INTCONSTANT
	|		DOUBLECONSTANT
	|		TRUE
	|		FALSE
	|		STRINGCONSTANT
	|		TNULL
	;
%%

void yyerror(char *s) {
    fprintf(stderr, "An error was found in row %d and column %d!\n", row, column);
    error_found++;
}

int main(int argc, char** args){
	if(argc > 1){
    	yyin = fopen(args[1], "r");
        yyparse();

		if(!error_found){
			printf("Program compiled successfully!\n");
		}else{
			printf("Program finished with %d error(s)!\n", error_found);
		}
		
    }else{
    	fprintf(stderr, "ERROR: There is no file to analyze!\n");
    }

	return 0;
}
