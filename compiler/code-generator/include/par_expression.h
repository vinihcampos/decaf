#ifndef _PAR_EXPRESSION_
#define _PAR_EXPRESSION_

#include <string>

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
		std::string generate(){
			std::string code = "";
			code += "(";
			if(expression != nullptr){
				code += expression->generate();
			}
			code += ")";

			return code;
		}
};

#endif