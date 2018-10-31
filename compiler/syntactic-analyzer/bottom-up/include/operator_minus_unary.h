#ifndef _OPERATOR_MINUS_UNARY_
#define _OPERATOR_MINUS_UNARY_

#include "operator_unary.h"

class OperatorMinusUnary : public OperatorUnary{
	public:
		OperatorMinusUnary(Expression * expression_) : OperatorUnary(expression_) {}
		void toString(){
			std::cout << "OperatorMinusUnary: {";
			if(expression != nullptr){
				std::cout << "expression: ";
				expression->toString();
				std::cout << ",";
			}
			std::cout << "}";
		}
};

#endif