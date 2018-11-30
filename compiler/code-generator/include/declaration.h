#ifndef _DECLARATION_
#define _DECLARATION_

#include <iostream>
#include <string.h>
#include "symbol.h"

class Declaration{
	public:
		virtual void toString(){
		}
		virtual std::string generate(){ return ""; }
		virtual Symbol table(){
			Symbol s;
			return s;
		}
};

#endif