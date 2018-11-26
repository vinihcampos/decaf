#ifndef _DEC_VARIABLE_LIST_
#define _DEC_VARIABLE_LIST_

#include <string>
#include <iostream>
#include <deque>
#include "declaration_variable.h"

class DeclarationVariableList{

	public:
		std::deque<DeclarationVariable> variables;
		DeclarationVariableList(std::deque<DeclarationVariable> variables_) : variables{variables_} {}
		void toString(){
			std::cout << "[";
			if(variables.size() > 0){
				for(int i = 0; i < variables.size(); ++i){
					std::cout << "{";
					variables[i].toString();
					std::cout << "}";
				}
			}
			std::cout << "]" ;
		}

		std::string generate(){
			std::string code = "";
			for (int i = 0; i < variables.size(); ++i){
				code += variables[i].generate() + "\n";
			}
			return code;
		}

};

#endif