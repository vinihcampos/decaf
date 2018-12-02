#ifndef _STMT_RETURN_
#define _STMT_RETURN_

#include <string>
#include "stmt.h"
#include "stmt_expression.h"
#include "static.h"
#include "symbol.h"

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
			std::string code = "";
			if(Static::currFun[0] != '-' && Static::currFun.compare("")){
				std::string name = Static::currFun;
				code += "return_" + name + " = " + expression->generate();
				code += "\n" + name + " auxReturn = stack_" + name + ".top();\n";
				code += "stack_" + name + ".pop();\n";
				code += "label = auxReturn.label;\n";
				code += "goto labels;";
			}

			return code;
		}
};

#endif