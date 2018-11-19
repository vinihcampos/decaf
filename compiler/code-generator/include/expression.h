#ifndef _EXPRESSION_
#define _EXPRESSION_

#include "stmt.h"

class Expression{
	public:
		virtual void toString(){
		}
		virtual void generate(){}
};

#endif