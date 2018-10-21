#ifndef _STMT_RETURN_
#define _STMT_RETURN_

#include "stmt.h"
#include "expression.h"

class StatementReturn : Statement{
	
	public:
		Expression expression;
};

#endif