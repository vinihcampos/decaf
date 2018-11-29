#ifndef _STMT_RETURN_
#define _STMT_RETURN_

#include <string>
#include "stmt.h"
#include "stmt_expression.h"
#include "static.h"

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
		std::string generate() override{
			return !Static::currFun.compare("") ? "" : "return_" + Static::currFun + " = " + expression->generate();
		}
};

#endif