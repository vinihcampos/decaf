#ifndef _STMT_BLOCK_
#define _STMT_BLOCK_

#include <deque>
#include <string>
#include <iostream>

#include "declaration_variable.h"
#include "declaration_variable_list.h"
#include "stmt_list.h"

class StatementBlock : public Statement{

	public:
		DeclarationVariableList variables;
		StatementList statements;

		StatementBlock(DeclarationVariableList variables_, StatementList statements_) : 
			variables{variables_}, statements{statements_}{}

		void toString() override{
			std::cout << "{" ;
			std::cout << "DeclarationVariables: ";
			variables.toString();
			std::cout << ",";
			std::cout << "Statements: ";
			statements.toString();
			std::cout << "}" ;
		}

		std::string generate() override{
			std::string code = "";
			code += variables.generate();
			code += statements.generate();
			return code;
		}
};

#endif