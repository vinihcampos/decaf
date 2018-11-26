#ifndef _OPERATOR_OR_
#define _OPERATOR_OR_

#include <string>
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

		std::string generate() override{
		 	std::string code = "";
			code += expression1->generate();
			code += "||";
			code += expression2->generate();

			return code;
		}
};

#endif