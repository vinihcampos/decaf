#ifndef _DEC_CLASS_
#define _DEC_CLASS_

#include <string>
#include <deque>
#include <iostream>
#include "declaration.h"
#include "field.h"
#include "implements.h"
#include "static.h"

class DeclarationClass : public Declaration{

	public:
		std::string userType;
		std::string parent;
		Implements interfaces;
		Field fields;

		DeclarationClass(std::string userType_, std::string parent_, 
						 Implements interfaces_, Field fields_) : 
						 userType{userType_}, parent{parent_}, interfaces{interfaces_}, fields{fields_}{}

		void toString() override{
			std::cout << "DeclarationClass: {";
			std::cout << "userType: " << userType << ",";
			std::cout << "parent: " << parent << ",";
			std::cout << "Interfaces: ";
			interfaces.toString();
			std::cout << ",";
			fields.toString();
			std::cout << "}";
		}

		std::string generate() override{
			std::string code = "";

			return code;
		}
};

#endif