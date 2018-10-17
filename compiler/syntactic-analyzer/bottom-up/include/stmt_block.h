#ifndef _STMT_BLOCK_
#define _STMT_BLOCK_

#import <vector>
#import "declaration_variable.h"
#import "stmt.h"

class StatementBlock{

	public:
		std::vector<DeclarationVariable> variables;
		std::vector<Statement> statements;
};

#endif