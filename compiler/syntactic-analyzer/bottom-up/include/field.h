#ifndef _FIELD_
#define _FIELD__

#include <vector>
#include "declaration_variable.h"
#include "declaration_function.h"

class Field{

	public:
		std::vector<DeclarationVariable> variables;
		std::vector<DeclarationFunction> functions;

};

#endif