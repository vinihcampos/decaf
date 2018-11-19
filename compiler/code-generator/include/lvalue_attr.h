#ifndef _LVALUE_ATTR_
#define _LVALUE_ATTR_

#include <string>
#include "lvalue.h"

class LValueAttribute : public LValue{

	public:
		std::string id;
		Expression * expression1;

		LValueAttribute(std::string id_, Expression * expression1_) : id{id_}, expression1{expression1_} {}
		void toString(){
			std::cout << "LValueAttribute: {";
			if(expression1 != nullptr){
				std::cout << "expression: ";
				expression1->toString();
				std::cout << ",";
			}
			std::cout << "id: " << id;
			std::cout << "}";
		}
		void generate() override{
			std::cout << id << ".";
			expression1->generate();
		}
};

#endif