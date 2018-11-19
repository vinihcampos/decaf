#ifndef _STMT_WHILE_
#define _STMT_WHILE_

#include "stmt.h"
#include "expression.h"

class StatementWhile : public Statement{
	
	public:
		Expression * expression;
		Statement * whileStatement;
		StatementWhile(Expression * expression_, Statement * whileStatement_) :
			expression{expression_}, whileStatement{whileStatement_} {}
		void toString(){
			std::cout << "StatementWhile: {";
			if(expression != nullptr){
				std::cout << "condition: "; 
				expression->toString();
				std::cout << ",";
			}
			if(whileStatement != nullptr){
				std::cout << "statement: ";
				whileStatement->toString();
				std::cout << ",";
			}	
			std::cout << "}";
		}
		void generate() override{
		}
};

#endif