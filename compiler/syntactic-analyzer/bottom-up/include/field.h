#ifndef _FIELD_
#define _FIELD_

#include <deque>
#include "declaration_variable.h"
#include "declaration_function.h"

class Field{

	public:
		std::deque<DeclarationVariable*> variables;
		std::deque<DeclarationFunction*> functions;

		Field(std::deque<DeclarationVariable*> variables_, std::deque<DeclarationFunction*> functions_) :
			variables{variables_}, functions{functions_} {}

		void toString(){

		}

};

#endif