#ifndef _OPERATOR_BINARY_
#define _OPERATOR_BINARY_

#include "expression.h"

class OperatorBinary : public Expression{
	
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorBinary(Expression * expression1_, Expression * expression2_) :
			expression1{expression1_}, expression2{expression2_} {}

		virtual void toString(){
			std::cout << "binary!";
		}
};

#endif