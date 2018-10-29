#ifndef _NULL_CONSTANT_
#define _NULL_CONSTANT_

#include "constant.h"

class NullConstant : public Constant {
	public:
		std::string value = "NULL";
};

#endif