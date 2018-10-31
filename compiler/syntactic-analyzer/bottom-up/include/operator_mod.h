#ifndef _OPERATOR_MOD_
#define _OPERATOR_MOD_

#include "operator_binary.h"

class OperatorMod: public OperatorBinary{
	public:
		OperatorMod(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){
			std::cout << "OperatorMod: {";
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