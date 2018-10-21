#ifndef _DEC_VARIABLE_
#define _DEC_VARIABLE_

#include <string>
#import "declaration.h"
#import "type.h"

class DeclarationVariable : Declaration{

	public:
		Type type;
		std::string id;

};

#endif