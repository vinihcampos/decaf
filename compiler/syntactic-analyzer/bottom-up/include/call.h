#ifndef _CALL_
#define _CALL_

#include <string>
#include "expression.h"
#include "expression_list.h"

class Call : public Expression{

	public:
		std::string id;
		Expression * expression1;
		ExpressionList actuals;

		Call(std::string id_, Expression * expression1_, ExpressionList actuals_) : 
			id{id_}, expression1{expression1_}, actuals{actuals_} {}

		void toString(){

		}

};

#endif