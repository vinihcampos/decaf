#ifndef _OPERATOR_UNARY_
#define _OPERATOR_UNARY_

#include <string>

#include "expression.h"

class OperatorUnary : public Expression{
	
	public:
		Expression * expression;
		OperatorUnary(Expression * expression_) : expression{expression_} {}
		virtual void toString(){

		}

		virtual std::string generate(){
		}
};

#endif