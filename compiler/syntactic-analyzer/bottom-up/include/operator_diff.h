#ifndef _OPERATOR_DIFF_
#define _OPERATOR_DIFF_

#include "operator_binary.h"

class OperatorDiff : public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorDiff(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif