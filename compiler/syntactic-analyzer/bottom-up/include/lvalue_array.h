#ifndef _LVALUE_ARRAY_
#define _LVALUE_ARRAY_

#include <string>
#include "lvalue.h"

class LValueArray : public LValue{

	public:
		Expression * expression1;
		Expression * expression2;

		LValueArray(Expression * expression1_, Expression * expression2_) : 
			expression1{expression1_}, expression2{expression2_} {}

};

#endif