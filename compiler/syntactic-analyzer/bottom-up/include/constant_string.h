#ifndef _STRING_CONSTANT_
#define _STRING_CONSTANT_

#include "constant.h"
#include <string>

class StringConstant : Constant {
	public:
		std::string value;
};

#endif