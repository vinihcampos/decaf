#ifndef _PAR_EXPRESSION_
#define _PAR_EXPRESSION_

#include "expression.h"

class ParExpression : public Expression{
	public:
		Expression * expression;
		ParExpression(Expression * expression_) : expression{expression_}{}

		void toString(){
			std::cout << "ParExpression: {";
			if(expression != nullptr){
				expression->toString();
			}
			std::cout << "}";
		}
		void generate(){
			std::cout << "(";
			if(expression != nullptr){
				expression->generate();
			}
			std::cout << ")";
		}
};

#endif