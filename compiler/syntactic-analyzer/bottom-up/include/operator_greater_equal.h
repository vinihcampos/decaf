#ifndef _OPERATOR_GREATER_EQUAL_
#define _OPERATOR_GREATER_EQUAL_

#include "operator_binary.h"

class OperatorGreaterEqual : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorGreaterEqual(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif