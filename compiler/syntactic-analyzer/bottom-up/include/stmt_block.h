#ifndef _STMT_BLOCK_
#define _STMT_BLOCK_

#include <deque>
#include <iostream>
#include "declaration_variable.h"
#include "declaration_variable_list.h"
#include "stmt.h"

class StatementBlock : public Statement{

	public:
		DeclarationVariableList variables;
		std::deque<Statement*> statements;

		StatementBlock(DeclarationVariableList variables_, std::deque<Statement*> statements_) : 
			variables{variables_}, statements{statements_}{}

		void toString() override{
			std::cout << "{" << std::endl;
			std::cout << "\"DeclarationVariables\": ";
			variables.toString();
			std::cout << "\"Statements\": ";
			std::cout << "[";
			/*if(statements.size() > 0){
				for(int i = 0; i < statements.size(); ++i){
					std::cout << "{ ";
					statements[i]->toString();
					if(i + 1 >= statements.size()){
						std::cout << " }";
					}else{
						std::cout << " },";
					}
				}
			}*/
			std::cout << "]" << std::endl;
			std::cout << "}" << std::endl;
		}
};

#endif