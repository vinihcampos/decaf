#ifndef _STMT_EXPRESSION_
#define _STMT_EXPRESSION_

#include <string>

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
		std::string generate(){
			std::string code = "";
			if(expression != nullptr){
				code += expression->generate();
			}
			code +=";\n";

			return code;
		}
};

#endif