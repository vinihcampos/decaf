#ifndef _LVALUE_
#define _LVALUE_

#include <string>
#include "expression.h"

class LValue : Expression{

	public:
		std::string id;
		Expression expression1;
		Expression expression2;

};

#endif