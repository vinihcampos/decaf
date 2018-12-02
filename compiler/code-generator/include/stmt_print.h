#ifndef _STMT_PRINT_
#define _STMT_PRINT_

#include <string>
#include <deque>
#include "stmt.h"
#include "expression_list.h"

class StatementPrint : public Statement{
	
	public:
		ExpressionList expressions;
		StatementPrint(ExpressionList expressions_) : expressions{expressions_} {}
		void toString(){
			std::cout << "StatementPrint: {";
			std::cout << "expressions: ";
			expressions.toString();
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = "";
			code += "cout ";

			for (int i = 0; i < expressions.expressions.size(); ++i){
				code += "<< " + expressions.expressions[i]->generate();
			}

			code += "<< endl;";

			return code;
		}
};

#endif