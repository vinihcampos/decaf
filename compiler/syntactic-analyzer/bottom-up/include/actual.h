#ifndef _ACTUAL_
#define _ACTUAL_

#include "expression.h"
#include <deque>

class Actual {

	public:
		std::deque<Expression*> expressions;
		Actual(std::deque<Expression*> expressions_) : expressions{expressions_} {}

};

#endif