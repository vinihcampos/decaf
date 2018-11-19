#ifndef _LVALUE_
#define _LVALUE_

#include <string>
#include "expression.h"

class LValue : public Expression{
	public:
		virtual void toString(){			
		}
		virtual void generate() override{}
};

#endif