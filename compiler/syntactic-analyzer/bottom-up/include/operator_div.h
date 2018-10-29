#ifndef _OPERATOR_DIV_
#define _OPERATOR_DIV_

#include "operator_binary.h"

class OperatorDiv: public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorDiv(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif