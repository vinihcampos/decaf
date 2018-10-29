#ifndef _OPERATOR_LESS_EQUAL_
#define _OPERATOR_LESS_EQUAL_

#include "operator_binary.h"

class OperatorLessEqual : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorLessEqual(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif