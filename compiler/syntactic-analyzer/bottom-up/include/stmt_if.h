#ifndef _STMT_IF_
#define _STMT_IF_

#include "stmt.h"
#include "expression.h"
#include <iostream>

class StatementIf : public Statement{
	
	public:
		Expression * expression;
		Statement * ifStatement;
		Statement * elseStatement;
		StatementIf(Expression * expression_, Statement * ifStatement_, Statement * elseStatement_) :
			expression{expression_}, ifStatement{ifStatement_}, elseStatement{elseStatement_} {}
		void toString(){
			std::cout << "StatementIf: {";
			if(expression != nullptr){
				std::cout << "condition: "; 
				expression->toString();
				std::cout << ",";
			}
			if(ifStatement != nullptr){
				std::cout << "statement: ";
				ifStatement->toString();
				std::cout << ",";
			}			
			if(elseStatement != nullptr){
				std::cout << "elseStatement: ";
				elseStatement->toString();
				std::cout << ",";
			}
			std::cout << "}";
		}
};

#endif