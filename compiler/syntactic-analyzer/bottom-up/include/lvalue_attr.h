#ifndef _LVALUE_ATTR_
#define _LVALUE_ATTR_

#include <string>
#include "lvalue.h"

class LValueAttribute : public LValue{

	public:
		std::string id;
		Expression * expression1;

		LValueAttribute(std::string id_, Expression * expression1_) : id{id_}, expression1{expression1_} {}

};

#endif