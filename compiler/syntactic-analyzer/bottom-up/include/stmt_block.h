#ifndef _STMT_BLOCK_
#define _STMT_BLOCK_

#include <deque>
#include <iostream>
#include "declaration_variable.h"
#include "stmt.h"

class StatementBlock : public Statement{

	public:
		std::deque<DeclarationVariable*> variables;
		std::deque<Statement*> statements;

		StatementBlock(){}
		StatementBlock(std::deque<DeclarationVariable*> variables_, std::deque<Statement*> statements_) : 
			variables{variables_}, statements{statements_}{}

		void toString() override{
			std::cout << "{}";
		}
};

#endif