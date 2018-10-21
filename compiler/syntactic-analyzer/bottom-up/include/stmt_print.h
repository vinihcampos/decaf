#ifndef _STMT_PRINT_
#define _STMT_PRINT_

#include <vector>
#include "stmt.h"
#include "expression.h"

class StatementPrint : Statement{
	
	public:
		std::vector<Expression> expressions;
};

#endif