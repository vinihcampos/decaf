#ifndef _EXPRESSION_THIS_
#define _EXPRESSION_THIS_

#include <string>

#include "expression.h"

class ThisExpression : public Expression{
	public:
		void toString(){
			std::cout << "ThisExpression: { this }"; 
		}
		std::string generate(){
			return "";
		}
};

#endif