#ifndef _EXPRESSION_
#define _EXPRESSION_

#include <string>

#include "stmt.h"

class Expression{
	public:
		virtual void toString(){
		}
		virtual std::string generate(){ return ""; }
};

#endif