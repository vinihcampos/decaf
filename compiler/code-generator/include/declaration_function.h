#ifndef _DEC_FUNCTION_
#define _DEC_FUNCTION_

#include <string>
#include <vector>
#include <iostream>
#include "declaration.h"
#include "type.h"
#include "formal.h"
#include "stmt_block.h"

class DeclarationFunction : public Declaration{

	public:
		Type type;
		std::string id;
		Formal formals;
		StatementBlock stmtBlock;

		DeclarationFunction(Type type_, std::string id_, Formal formals_, StatementBlock stmtBlock_) : 
		type{type_}, id{id_}, formals{formals_}, stmtBlock{stmtBlock_}{}
		
		void toString() override{
			std::cout << "DeclarationFunction: { " ;
			std::cout << "id: " << id << "," ;
			type.toString();
			std::cout << "," ;
			std::cout << "formals: "; formals.toString();
			std::cout << "," ;
			std::cout << "StatementBlock: "; stmtBlock.toString();
			std::cout << "}";
		}

		void generate() override{
			stmtBlock.generate();
		}
};

#endif