%{
	int yylex();
	void yyerror(char *s) { EM_error(EM_tokPos, "%s", s); }
%}
%token VOID INT DOUBLE BOOL STRING CLASS INTERFACE NULL THIS EXTENDS IMPLEMENTS FOR WHILE IF ELSE RETURN BREAK NEW NEWARRAY PRINT READINTEGER READLINE ID USERTYPE INTCONSTANT DOUBLECONSTANT TRUE FALSE STRINGCONSTANT UMINUS L LEQ G GEQ EQ NEQ AND OR EOF
%start program
%%

program:	decl
	|		%empty
	;

decl:	variableDecl
	|	functionDecl
	|	classDecl
	|	interfaceDecl
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
	|	ID
	|	type '[' ']'
	;

functionDecl:	type ID '(' formals ')' stmtBlock
	|			VOID ID '(' formals ')' stmtBlock
	;

formals:	variable formals1
	|		%empty
	;

formals1:	',' variable
	|		%empty
	;

classDecl:	CLASS ID extends implements '{' field '}'
	;

extends:	EXTENDS ID
	|		%empty
	;

implements:	IMPLEMENTS ID implements1
	|		%empty
	;

implements1:	',' ID implements1
	|			%empty
	;

field:	variableDecl
	|	functionDecl
	|	%empty
	;

interfaceDecl:	INTERFACE ID '{' prototype '}'
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
	|	expr '-' expr
	|	'-' expr
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
	|	NEW '(' ID ')'
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
	|		NULL
	;

%%