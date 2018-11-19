#ifndef _BOOL_CONSTANT_
#define _BOOL_CONSTANT_

#include "constant.h"
#include <string>

class BoolConstant : public Constant {
	public:
		bool value;
		BoolConstant(bool value_) : value{value_} {}
		void toString(){
			std::cout << "BoolConstant: {";
			std::cout << "value: " << (value == true ? "true" : "false");
			std::cout << "}";
		}

		std::string generate() override{
			std::string code = "";
			code += std::to_string(value); 

			return code;
		}
};

#endif