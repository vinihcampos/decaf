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
			std::cout << "variables: [";
			for(int i = 0; i < variables.size(); ++i){
				if(variables[i] != nullptr){
					variables[i]->toString();
					std::cout << ",";
				}
			}
			std::cout << "],";
			std::cout << "functions: [";
			for(int i = 0; i < functions.size(); ++i){
				if(functions[i] != nullptr){
					functions[i]->toString();
					std::cout << ",";
				}
			}
			std::cout << "],";
		}

};

#endif