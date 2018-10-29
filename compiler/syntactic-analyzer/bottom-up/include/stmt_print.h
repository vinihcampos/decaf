#ifndef _STMT_PRINT_
#define _STMT_PRINT_

#include <deque>
#include "stmt.h"
#include "expression.h"

class StatementPrint : public Statement{
	
	public:
		std::deque<Expression*> expressions;
		StatementPrint(std::deque<Expression*> expressions_) : expressions{expressions_} {}
		void toString(){
			
		}
};

#endif