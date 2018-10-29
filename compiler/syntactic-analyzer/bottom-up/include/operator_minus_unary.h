#ifndef _OPERATOR_MINUS_UNARY_
#define _OPERATOR_MINUS_UNARY_

#include "operator_unary.h"

class OperatorMinusUnary : public OperatorUnary{
	public:
		Expression * expression;
		OperatorMinusUnary(Expression * expression_) : OperatorUnary(expression_) {}
		virtual void toString(){

		}
};

#endif