#ifndef _OPERATOR_MOD_
#define _OPERATOR_MOD_

#include "operator_binary.h"

class OperatorMod: public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorMod(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif