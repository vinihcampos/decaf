#ifndef _SYMBOL_
#define _SYMBOL_

#include <string>
#include <vector>
#include "type.h"

class Symbol{
	public:
		Type type;
		std::string id;
		std::string parent;
		std::vector<std::string> params;
};

#endif