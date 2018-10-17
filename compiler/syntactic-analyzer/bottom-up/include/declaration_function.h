#ifndef _DEC_FUNCTION_
#define _DEC_FUNCTION_

#import <string>
#import <vector>
#import "declaration.h"
#import "type.h"
#import "formal.h"
#import "stmt_block.h"

class DeclarationFunction : Declaration{

	public:
		Type type;
		std::string id;
		Formal formals;
		StatementBlock statementBlock;

};

#endif