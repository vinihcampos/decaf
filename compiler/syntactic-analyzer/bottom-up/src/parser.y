%{
	#include <cstdio>
	#include <deque>
	#include "program.h"
	#include "declaration_class.h"
	#include "declaration_function.h"
	#include "declaration_interface.h"
	#include "declaration_variable.h"
	#include "formal.h"
	#include "stmt_block.h"
	#include "stmt.h"
	#include "type.h"
	
	extern int row, column;
	extern char * lexeme;
	extern FILE* yyin;
	int yylex();
	void yyerror(char *);
	extern FILE* yyin;
	int error_found = 0;

	Program program;

%}
%token <lexeme> VOID INT DOUBLE BOOL STRING CLASS INTERFACE TNULL THIS EXTENDS IMPLEMENTS FOR WHILE IF ELSE RETURN BREAK NEW NEWARRAY PRINT READINTEGER READLINE ID USERTYPE INTCONSTANT DOUBLECONSTANT TRUE FALSE STRINGCONSTANT UMINUS L LEQ G GEQ EQ NEQ AND OR

%union{
	Declaration * decl;
	DeclarationVariable * variableDecl;
	std::deque<DeclarationVariable*> * variableDeclList;
	DeclarationFunction * functionDecl;
	Formal * formal;
	Statement * stmt;
	StatementBlock * stmtBlock;
	std::deque<Statement*> * stmtList;
	Type * type;
	char * lexeme;
}

%type <decl> decl
%type <variableDecl> variableDecl variable 
%type <functionDecl> functionDecl
%type <type> type
%type <formal> formals formals1
%type <stmtBlock> stmtBlock
%type <variableDeclList> variableDeclList
%type <stmt> stmt
%type <stmtList> stmtList

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

program:	decl program {program.declarations.push_front($1);}
	|		%empty
	;

decl:	variableDecl  {$$ = $1;}
	|	functionDecl  {$$ = $1;}
	|	classDecl     {DeclarationClass class_; Declaration * dec = &class_; $$ = dec; }
	|	interfaceDecl {DeclarationInterface interface; Declaration * dec = &interface; $$ = dec; }
	|	error
	;

variableDecl:	variable ';' {$$ = $1;}
	;

variableDeclList:	variableDecl variableDeclList{
						$2->push_front($1);
						$$ = $2;
					}
	|				%empty {std::deque<DeclarationVariable*> decs; $$ = &decs; }
	;

variable:	type ID {DeclarationVariable * var = new DeclarationVariable(*$1, $2); $$ = var;}
	;

type:	INT  { Type * t = new Type(INT_T, 0); $$ = t;}
	|	DOUBLE { Type * t = new Type(DOUBLE_T, 0); $$ = t;}
	|	BOOL { Type * t = new Type(BOOL_T, 0); $$ = t;}
	|	STRING { Type * t = new Type(STRING_T, 0); $$ = t;}
	|	USERTYPE { Type * t = new Type(USERTYPE_T, 0); $$ = t;}
	|	type '[' ']' {Type * t = $1; t->size += 1; $$ = t; }
	;

functionDecl:	type ID '(' formals ')' stmtBlock {
					DeclarationFunction * fun = new DeclarationFunction(*$1, $2, *$4, *$6); 
					$$ = fun;
				}
	|			VOID ID '(' formals ')' stmtBlock {
					Type t = Type(VOID_T, 0); 
					DeclarationFunction * fun = new DeclarationFunction(t, $2, *$4, *$6); 
					$$ = fun;
				}
	;

formals:	variable formals1{
				$2->variables.push_front(*$1);
				$$ = $2;
			}
	|		%empty {$$ = new Formal();}
	;

formals1:	',' variable formals1 {
				$3->variables.push_front(*$2);
				$$ = $3;
			}
	|		%empty {$$ = new Formal();}
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

stmtBlock:	'{' variableDeclList stmtList '}' {
			StatementBlock * block = new StatementBlock(*$2, *$3);
			$$ = block;
		}
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

stmtList:	stmt stmtList {$$ = $2;}
	|		%empty { std::deque<Statement*> stmts; $$ = &stmts;}
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

    printf("Program size: %d\n", program.declarations.size());
    for(int i = 0; i < program.declarations.size(); ++i){
    	program.declarations[i]->toString();
    }

	return 0;
}
