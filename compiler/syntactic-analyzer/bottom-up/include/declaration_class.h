#ifndef _DEC_CLASS_
#define _DEC_CLASS_

#include <string>
#include <deque>
#include <iostream>
#include "declaration.h"
#include "field.h"

class DeclarationClass : public Declaration{

	public:
		std::string userType;
		std::string parent;
		std::deque<std::string> interfaces;
		Field fields;

		DeclarationClass(std::string userType_, std::string parent_, 
						 std::deque<std::string> interfaces_, Field fields_) : 
						 userType{userType_}, parent{parent_}, interfaces{interfaces_}, fields{fields_}{}

		void toString() override{
			
		}
};

#endif