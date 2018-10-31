#ifndef _OPERATOR_DIFF_
#define _OPERATOR_DIFF_

#include "operator_binary.h"

class OperatorDiff : public OperatorBinary{
	public:
		OperatorDiff(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){
			std::cout << "OperatorDiff: {";
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