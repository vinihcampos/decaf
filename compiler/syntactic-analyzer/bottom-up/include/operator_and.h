#ifndef _OPERATOR_AND_
#define _OPERATOR_AND_

#include "operator_binary.h"

class OperatorAnd : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorAnd(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif