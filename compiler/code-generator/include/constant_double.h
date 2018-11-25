#ifndef _DOUBLE_CONSTANT_
#define _DOUBLE_CONSTANT_

#include "constant.h"

class DoubleConstant : public Constant {
	public:
		double value;

		DoubleConstant(double value_) : value{value_} {}
		void toString(){
			std::cout << "DoubleConstant: {";
			std::cout << "value: " << value;
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = "";
			code += std::to_string(value);; 

			return code;
		}
};

#endif