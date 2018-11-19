#ifndef _OPERATOR_OR_
#define _OPERATOR_OR_

#include "operator_binary.h"

class OperatorOr : public OperatorBinary{
	public:
		OperatorOr(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){
			std::cout << "OperatorOr: {";
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

		void generate() override{
			expression1->generate();
			std::cout << "||";
			expression2->generate();
		}
};

#endif