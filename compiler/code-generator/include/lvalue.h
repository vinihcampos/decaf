#ifndef _LVALUE_
#define _LVALUE_

#include <string>
#include "expression.h"

class LValue : public Expression{
	public:
		virtual void toString(){			
		}
		virtual std::string generate() { return ""; }
};

#endif