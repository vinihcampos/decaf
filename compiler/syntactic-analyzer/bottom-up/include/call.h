#ifndef _CALL_
#define _CALL_

#include <string>
#include <vector>
#include "expression.h"
#include "actual.h"


class Call {

	public:
		std::string id;
		Expression expression1;
		std::vector<Actual> actuals;

};

#endif