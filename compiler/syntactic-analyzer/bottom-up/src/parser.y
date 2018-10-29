%{
	#include <cstdio>
	#include <deque>
	#include <string>
	#include "program.h"
	#include "declaration_class.h"
	#include "declaration_function.h"
	#include "declaration_interface.h"
	#include "declaration_variable.h"
	#include "formal.h"
	#include "field.h"
	#include "prototype.h"
	#include "stmt_block.h"
	#include "stmt.h"
	#include "type.h"
	#include "expression.h"
	#include "expression_this.h"
	#include "operator_assignment.h"
	#include "operator_plus.h"
	#include "operator_minus.h"
	#include "operator_multi.h"
	#include "operator_div.h"
	#include "operator_mod.h"
	#include "operator_less.h"
	#include "operator_less_equal.h"
	#include "operator_greater.h"
	#include "operator_greater_equal.h"
	#include "operator_equal.h"
	#include "operator_diff.h"
	#include "operator_and.h"
	#include "operator_or.h"
	#include "operator_minus_unary.h"
	#include "operator_not.h"
	#include "call.h"
	#include "lvalue.h"
	#include "lvalue_id.h"
	#include "lvalue_attr.h"
	#include "lvalue_array.h"
	#include "constant.h"
	#include "constant_int.h"
	#include "constant_double.h"
	#include "constant_string.h"
	#include "constant_bool.h"
	#include "constant_null.h"
	#include "read_integer.h"
	#include "read_line.h"
	#include "new.h"
	#include "new_array.h"

	
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
	DeclarationInterface * interfaceDecl;
	DeclarationClass * classDecl;
	std::deque<Prototype*> * prototype;
	Formal * formal;
	Field * field;
	Statement * stmt;
	StatementBlock * stmtBlock;
	std::deque<Statement*> * stmtList;
	Type * type;
	char * lexeme;
	char * extends;
	std::deque<std::string> * implements;
	Expression * expr;
	std::deque<Expression*> * exprList;
	LValue * lValue;
	Call * call;
	Constant * constant;
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
%type <interfaceDecl> interfaceDecl
%type <prototype> prototype
%type <classDecl> classDecl
%type <extends> extends
%type <implements> implements implements1
%type <field> field
%type <expr> expr expr1
%type <lValue> lValue
%type <constant> constant
%type <call> call
%type <exprList> exprList exprList1

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
	|	classDecl     {$$ = $1;}
	|	interfaceDecl {$$ = $1;}
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

classDecl:	CLASS USERTYPE extends implements '{' field '}' {
				$$ = new DeclarationClass($2, $3, *$4, *$6);
			}
	;

extends:	EXTENDS USERTYPE {$$ = $2;}
	|		%empty {$$ = "";}
	;

implements:	IMPLEMENTS USERTYPE implements1 {
				$3->push_front($2);
				$$ = $3;
			}
	|		%empty {std::deque<std::string> impl; $$ = &impl;}
	;

implements1:	',' USERTYPE implements1{
					$3->push_front($2);
					$$ = $3;
				}
	|			%empty {std::deque<std::string> impl; $$ = &impl;}
	;

field:	variableDecl field { $2->variables.push_front($1); $$ = $2; }
	|	functionDecl field { $2->functions.push_front($1); $$ = $2; }
	|	%empty {
			std::deque<DeclarationVariable*> vars;
			std::deque<DeclarationFunction*> funs;
			$$ = new Field(vars, funs);
		}
	;

interfaceDecl:	INTERFACE USERTYPE '{' prototype '}' {
			$$ = new DeclarationInterface($2, *$4);
		}
	;

prototype:	type ID '(' formals ')' ';' prototype {
				$7->push_front(new Prototype(*$1, $2, *$4));
				$$ = $7;
			}
	|		VOID ID '(' formals ')' ';' prototype {
				Type t = Type(VOID_T, 0);
				$7->push_front(new Prototype(t, $2, *$4));
				$$ = $7;
			}
	|		%empty {std::deque<Prototype*> proto; $$ = &proto;}
	;

stmtBlock:	'{' variableDeclList stmtList '}' {
			StatementBlock * block = new StatementBlock(*$2, *$3);
			$$ = block;
		}
	;

stmt:	expr1 ';' { $$ = $1; }
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

expr:	lValue '=' expr { $$ = new OperatorAssignment($1, $3); }
	|	constant { $$ = $1; }
	|	lValue { $$ = $1; }
	|	THIS { $$ = new ThisExpression(); }
	|	call { $$ = $1; }
	|	'(' expr ')' { $$ = $2; }
	|	expr '+' expr { $$ = new OperatorPlus($1, $3); }
	|	expr '-' expr { $$ = new OperatorMinus($1, $3); }
	|	expr '*' expr { $$ = new OperatorMulti($1, $3); }
	|	expr '/' expr { $$ = new OperatorDiv($1, $3); }
	|	expr '%' expr { $$ = new OperatorMod($1, $3); }
	|	'-' expr %prec UMINUS { $$ = new OperatorMinusUnary($2); }
	|	expr L expr { $$ = new OperatorLess($1, $3); }
	|	expr LEQ expr { $$ = new OperatorLessEqual($1, $3); }
	|	expr G expr { $$ = new OperatorGreater($1, $3); }
	|	expr GEQ expr { $$ = new OperatorGreaterEqual($1, $3); }
	|	expr EQ expr { $$ = new OperatorEqual($1, $3); }
	|	expr NEQ expr { $$ = new OperatorDiff($1, $3); }
	|	expr AND expr { $$ = new OperatorAnd($1, $3); }
	|	expr OR expr { $$ = new OperatorOr($1, $3); }
	|	'!' expr { $$ = new OperatorNot($2); }
	|	READINTEGER '(' ')' { $$ = new ReadInteger(); }
	|	READLINE '(' ')' { $$ = new ReadLine(); }
	|	NEW '(' USERTYPE ')' { $$ = new New($3); }
	|	NEWARRAY '(' expr ',' type ')' { $$ = new NewArray(*$5, $3); }
	;

exprList:	expr exprList1 { $2->push_front($1); $$ = $2; }
	|		%empty { std::deque<Expression*> exprs; $$ = &exprs; }
	;

exprList1:	',' expr exprList1 { $3->push_front($2); $$ = $3; }
	|		%empty { std::deque<Expression*> exprs; $$ = &exprs; }
	;

expr1:	expr { $$ = $1; }
	|	%empty { $$ = nullptr; }
	;

lValue:	ID { $$ = new LValueId($1); }
	|	expr '.' ID { $$ = new LValueAttribute($3, $1); }
	|	expr '[' expr ']' {$$ = new LValueArray($1, $3);}
	;

call:	ID '(' exprList ')' { $$ = new Call($1, nullptr, *$3); }
	|	expr '.' ID '(' exprList ')' { $$ = new Call($3, $1, *$5); }
	;

constant:	INTCONSTANT { $$ = new IntConstant(std::stoi($1)); }
	|		DOUBLECONSTANT { $$ = new DoubleConstant(std::stod($1)); }
	|		TRUE { $$ = new BoolConstant(true); }
	|		FALSE { $$ = new BoolConstant(false); }
	|		STRINGCONSTANT { $$ = new StringConstant($1); }
	|		TNULL { $$ = new NullConstant(); }
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
