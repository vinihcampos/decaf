#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "stmt.h"

class Expression : public Statement{
	public:
		virtual void toString(){
			std::cout << "EXPRESSION!";
		}
};

#endif