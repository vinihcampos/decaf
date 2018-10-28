#ifndef _FORMAL_
#define _FORMAL_

#include <deque>
#include <iostream>
#include "declaration_variable.h"

class Formal{

	public:
		std::deque<DeclarationVariable> variables;
		void toString(){
			if(variables.size() > 0){
				std::cout << "(";
				for(int i = 0; i < variables.size(); ++i){
					variables[i].toString();
				}
				std::cout << ")";
			}else{
				std::cout << "()";
			}
		}

};

#endif