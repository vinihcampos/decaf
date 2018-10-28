#ifndef _DEC_VARIABLE_
#define _DEC_VARIABLE_

#include <string>
#include "declaration.h"
#include "type.h"

class DeclarationVariable : Declaration{

	public:
		Type type;
		std::string id;

};

#endif