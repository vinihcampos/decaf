#ifndef _STMT_EXPRESSION_
#define _STMT_EXPRESSION_

#include "stmt.h"
#include "expression.h"

class StatementExpression : public Statement{
	public:
		Expression * expression;
		StatementExpression(Expression * expression_) : expression{expression_}{}

		void toString(){
			std::cout << "StatementExpression: {";
			if(expression != nullptr){
				expression->toString();
			}
			std::cout << "}";
		}
		void generate(){
			std::cout << "\t";
			if(expression != nullptr){
				expression->generate();
			}
			std::cout << ";" << std::endl;
		}
};

#endif