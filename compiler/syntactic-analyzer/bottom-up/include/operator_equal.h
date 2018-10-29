#ifndef _OPERATOR_EQUAL_
#define _OPERATOR_EQUAL_

#include "operator_binary.h"

class OperatorEqual: public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorEqual(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif