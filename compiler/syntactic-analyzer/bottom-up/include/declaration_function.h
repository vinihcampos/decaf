#ifndef _DEC_FUNCTION_
#define _DEC_FUNCTION_

#include <string>
#include <vector>
#include "declaration.h"
#include "type.h"
#include "formal.h"
#include "stmt_block.h"

class DeclarationFunction : Declaration{

	public:
		Type type;
		std::string id;
		Formal formals;
		StatementBlock statementBlock;

};

#endif