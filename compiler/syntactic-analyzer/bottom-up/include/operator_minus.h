#ifndef _OPERATOR_MINUS_
#define _OPERATOR_MINUS_

#include "operator_binary.h"

class OperatorMinus : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorMinus(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}	
};

#endif