#ifndef _OPERATOR_MULT_
#define _OPERATOR_MULT_

#include "operator_binary.h"

class OperatorMulti: public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorMulti(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif