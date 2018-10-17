#ifndef _FIELD_
#define _FIELD__

#import <vector>
#import "declaration_variable.h"
#import "declaration_function.h"

class Field{

	public:
		std::vector<DeclarationVariable> variables;
		std::vector<DeclarationFunction> functions;

};

#endif