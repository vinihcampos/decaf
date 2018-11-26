#ifndef _NULL_CONSTANT_
#define _NULL_CONSTANT_

#include "constant.h"

class NullConstant : public Constant {
	public:
		std::string value = "NULL";
		void toString(){
			std::cout << "NullConstant: {";
			std::cout << "value: " << value;
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = "";
			code += "nullptr"; 

			return code;
		}
};

#endif