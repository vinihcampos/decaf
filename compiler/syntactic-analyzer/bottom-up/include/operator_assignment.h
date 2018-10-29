#ifndef _OPERATOR_ASSIGNMENT_
#define _OPERATOR_ASSIGNMENT_

#include "operator_binary.h"

class OperatorAssignment: public OperatorBinary{
	public:
		Expression * expression1;
		Expression * expression2;

		OperatorAssignment(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){

		}
};

#endif