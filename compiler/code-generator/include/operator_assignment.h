#ifndef _OPERATOR_ASSIGNMENT_
#define _OPERATOR_ASSIGNMENT_

#include <string>

#include "operator_binary.h"
#include "read_integer.h"
#include "read_line.h"
#include "call.h"

class OperatorAssignment: public OperatorBinary{
	public:
		OperatorAssignment(Expression * expression1_, Expression * expression2_) :
			OperatorBinary(expression1_, expression2_) {}

		void toString(){
			std::cout << "OperatorAssignment: {";
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

			if (ReadInteger* t = dynamic_cast<ReadInteger*>(expression2)) {
		        code += "scanf(\"\%d\", &readIntAux);\n";
		        code += expression1->generate();
				code += "= readIntAux";
		    }else if (ReadLine* t = dynamic_cast<ReadLine*>(expression2)) {
		        code += "getline(cin, readStringAux);\n";
		        code += expression1->generate();
				code += "= readStringAux";
		    }else if (Call* t = dynamic_cast<Call*>(expression2)) {
		        code += expression2->generate();
		        code += expression1->generate() + " = return_fun_" + t->id;
		    }else{
		    	code += expression1->generate();
				code += " = ";
				code += expression2->generate();	
		    }			

			return code;
		}
};

#endif