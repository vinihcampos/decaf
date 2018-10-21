#ifndef _STMT_FOR_
#define _STMT_FOR_

#include "stmt.h"
#include "expression.h"

class StatementFor : Statement{
	
	public:
		Expression expression1;
		Expression expression2;
		Expression expression3;
		Statement forStatement;
};

#endif