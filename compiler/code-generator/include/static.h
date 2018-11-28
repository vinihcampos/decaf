#ifndef _STATIC_VALUES_
#define _STATIC_VALUES_

#include <string>
#include <map>
#include "symbol.h"

class Static{
	public:
		static int pc;
		static std::string d;
		static std::string structs;
		static std::string blocks;
		static std::string stacks;
		static std::map<std::string, Symbol> table;	
};

#endif