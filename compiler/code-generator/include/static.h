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
		static std::string returns;
		static std::string currFun;
		static std::string currClass;
		static std::string declarationFunctions;
		static std::map<std::string, Symbol> table;
		static std::map<std::string, int> funId;
};

#endif