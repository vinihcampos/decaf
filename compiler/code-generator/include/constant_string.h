#ifndef _STRING_CONSTANT_
#define _STRING_CONSTANT_

#include "constant.h"
#include <string>

class StringConstant : public Constant {
	public:
		std::string value;
		StringConstant(std::string value_) : value{value_} {}
		void toString(){
			std::cout << "StringConstant: {";
			std::cout << "value: " << value;
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = value; 
			return code;
		}
};

#endif