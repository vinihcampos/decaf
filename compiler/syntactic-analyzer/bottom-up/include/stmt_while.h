#ifndef _STMT_WHILE_
#define _STMT_WHILE_

#include "stmt.h"
#include "expression.h"

class StatementWhile : Statement{
	
	public:
		Expression expression;
		Statement whileStatement;
};

#endif