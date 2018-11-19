#ifndef _STMT_RETURN_
#define _STMT_RETURN_

#include "stmt.h"
#include "stmt_expression.h"

class StatementReturn : public Statement{
	
	public:
		StatementExpression * expression;
		StatementReturn(StatementExpression * expression_) : expression{expression_} {}
		void toString(){
			std::cout << "StatementReturn: {";
			if(expression != nullptr){
				std::cout << "expression: ";
				expression->toString();
			}
			std::cout << "}";
		}
		void generate() override{
		}
};

#endif