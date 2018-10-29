#ifndef _OPERATOR_PLUS_
#define _OPERATOR_PLUS_

#include "operator_binary.h"

class OperatorPlus : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorPlus(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif