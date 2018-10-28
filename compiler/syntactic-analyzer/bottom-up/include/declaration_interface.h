#ifndef _DEC_INTERFACE_
#define _DEC_INTERFACE_

#include <string>
#include <vector>
#include <iostream>
#include <iostream>
#include "declaration.h"
#include "prototype.h"

class DeclarationInterface : public Declaration{

	public:
		std::string userType;
		std::vector<Prototype> prototypes;

		void toString() override{
			
		}
};

#endif