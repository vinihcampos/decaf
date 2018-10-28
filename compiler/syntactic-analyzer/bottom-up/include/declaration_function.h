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
			type.toString();
			std::cout << id << std::endl;
			formals.toString();
			stmtBlock.toString();
		}
};

#endif