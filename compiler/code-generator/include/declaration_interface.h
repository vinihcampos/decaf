#ifndef _DEC_INTERFACE_
#define _DEC_INTERFACE_

#include <string>
#include <deque>
#include <iostream>
#include <iostream>
#include "declaration.h"
#include "prototype_list.h"

class DeclarationInterface : public Declaration{

	public:
		std::string userType;
		PrototypeList prototypes;

		DeclarationInterface(std::string userType_, PrototypeList prototypes_) :
			userType{userType_}, prototypes{prototypes_} {}

		void toString() override{
			std::cout << "DeclarationInterface: {";
			std::cout << "userType: " << userType << ",";
			std::cout << "prototypes: ";
			prototypes.toString();
			std::cout << "}";
		}

		std::string generate() override{
			std::string code = "";

			return code;
		}
};

#endif