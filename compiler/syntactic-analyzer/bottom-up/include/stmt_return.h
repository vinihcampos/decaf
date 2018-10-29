#ifndef _STMT_RETURN_
#define _STMT_RETURN_

#include "stmt.h"
#include "expression.h"

class StatementReturn : public Statement{
	
	public:
		Expression * expression;
		StatementReturn(Expression * expression_) : expression{expression_} {}
		void toString(){
			
		}
};

#endif