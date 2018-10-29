#ifndef _OPERATOR_NOT_
#define _OPERATOR_NOT_

#include "operator_unary.h"

class OperatorNot : public OperatorUnary{
	public:
		Expression * expression;
		OperatorNot(Expression * expression_) : OperatorUnary(expression_) {}
		virtual void toString(){

		}
};

#endif