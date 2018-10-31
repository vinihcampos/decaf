#ifndef _OPERATOR_LESS_
#define _OPERATOR_LESS_

#include "operator_binary.h"

class OperatorLess : public OperatorBinary{
	public:
		OperatorLess(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){
			std::cout << "OperatorLess: {";
			if(expression1 != nullptr){
				std::cout << "leftExpression: ";
				expression1->toString();
				std::cout << ",";
			}
			if(expression2 != nullptr){
				std::cout << "rightExpression: ";
				expression2->toString();
				std::cout << ",";
			}
			std::cout << "}";
		}	
};

#endif