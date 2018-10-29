#ifndef _OPERATOR_LESS_
#define _OPERATOR_LESS_

#include "operator_binary.h"

class OperatorLess : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorLess(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}	
};

#endif