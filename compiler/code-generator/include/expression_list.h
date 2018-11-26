#ifndef _EXPRESSION_LIST_
#define _EXPRESSION_LIST_

#include <string>

#include "expression.h"

class ExpressionList{
	public:
		std::deque<Expression*> expressions;
		ExpressionList(std::deque<Expression*> expressions_) : expressions{expressions_} {}
		void toString(){
			std::cout << "[";
			for(int i = 0; i < expressions.size(); ++i){
				expressions[i]->toString();
				std::cout << ",";
			}
			std::cout << "]";
		}
		std::string generate(){
			std::string code = "";
			for(int i = 0; i < expressions.size(); ++i){
				code += expressions[i]->generate();
			}
			
			return code;
		}

};

#endif