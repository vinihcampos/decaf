#ifndef _STMT_IF_
#define _STMT_IF_

#include "stmt.h"
#include "expression.h"

class StatementIf : Statement{
	
	public:
		Expression expression;
		Statement ifStatement;
		Statement elseStatement;
};

#endif