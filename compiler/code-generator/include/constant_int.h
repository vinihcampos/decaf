#ifndef _INT_CONSTANT_
#define _INT_CONSTANT_

#include "constant.h"
#include <string>

class IntConstant : public Constant {
	public:
		int value;
		IntConstant(int value_) : value{value_} {}
		void toString(){
			std::cout << "IntConstant: {";
			std::cout << "value: " << value;
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = "";
			code += std::to_string(value); 

			return code;
		}
};

#endif