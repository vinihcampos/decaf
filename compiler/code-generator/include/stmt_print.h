#ifndef _STMT_PRINT_
#define _STMT_PRINT_

#include <deque>
#include "stmt.h"
#include "expression_list.h"

class StatementPrint : public Statement{
	
	public:
		ExpressionList expressions;
		StatementPrint(ExpressionList expressions_) : expressions{expressions_} {}
		void toString(){
			std::cout << "StatementPrint: {";
			std::cout << "expressions: ";
			expressions.toString();
			std::cout << "}";
		}
		void generate() override{
		}
};

#endif