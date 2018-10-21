#ifndef _NEW_ARRAY_
#define _NEW_ARRAY_

#include "expression.h"
#include "type.h"

class NewArray : Expression{

	public:
		Type type;
		Expression expression;
};

#endif