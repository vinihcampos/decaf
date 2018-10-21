#ifndef _OPERATOR_BINARY_
#define _OPERATOR_BINARY_

#include "expression.h"

class OperatorBinary : Expression{
	
	public:
		Expression expression1;
		Expression expression2;
};

#endif