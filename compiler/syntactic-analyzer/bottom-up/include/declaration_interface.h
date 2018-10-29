#ifndef _DEC_INTERFACE_
#define _DEC_INTERFACE_

#include <string>
#include <deque>
#include <iostream>
#include <iostream>
#include "declaration.h"
#include "prototype.h"

class DeclarationInterface : public Declaration{

	public:
		std::string userType;
		std::deque<Prototype*> prototypes;

		DeclarationInterface(std::string userType_, std::deque<Prototype*> prototypes_) :
			userType{userType_}, prototypes{prototypes_} {}

		void toString() override{
			
		}
};

#endif