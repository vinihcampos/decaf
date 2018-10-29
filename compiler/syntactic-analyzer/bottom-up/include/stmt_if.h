#ifndef _STMT_IF_
#define _STMT_IF_

#include "stmt.h"
#include "expression.h"

class StatementIf : public Statement{
	
	public:
		Expression * expression;
		Statement * ifStatement;
		Statement * elseStatement;
		StatementIf(Expression * expression_, Statement * ifStatement_, Statement * elseStatement_) :
			expression{expression_}, ifStatement{ifStatement_}, elseStatement{elseStatement_} {}
		void toString(){
			
		}
};

#endif