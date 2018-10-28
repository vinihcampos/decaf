#ifndef _DEC_CLASS_
#define _DEC_CLASS_

#include <string>
#include <vector>
#include "declaration.h"
#include "field.h"

class DeclarationClass : Declaration{

	public:
		std::string userType;
		std::string parent;
		std::vector<std::string> interfaces;
		std::vector<Field> fields;
};

#endif