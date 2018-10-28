#ifndef _DEC_INTERFACE_
#define _DEC_INTERFACE_

#include <string>
#include <vector>
#include "declaration.h"
#include "prototype.h"

class DeclarationInterface : Declaration{

	public:
		std::string userType;
		std::vector<Prototype> prototypes;
};

#endif