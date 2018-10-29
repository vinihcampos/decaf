#ifndef _OPERATOR_GREATER_
#define _OPERATOR_GREATER_

#include "operator_binary.h"

class OperatorGreater : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorGreater(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif