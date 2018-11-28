#ifndef _SYMBOL_
#define _SYMBOL_

#include <string>
#include <vector>

class Symbol{
	public:
		std::string id;
		std::string parent;
		std::vector<std::string> params;	
};

#endif