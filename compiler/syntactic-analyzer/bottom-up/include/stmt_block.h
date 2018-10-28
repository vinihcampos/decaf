#ifndef _STMT_BLOCK_
#define _STMT_BLOCK_

#include <vector>
#include "declaration_variable.h"
#include "stmt.h"

class StatementBlock{

	public:
		std::vector<DeclarationVariable> variables;
		std::vector<Statement> statements;
};

#endif