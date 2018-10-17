#ifndef _DEC_INTERFACE_
#define _DEC_INTERFACE_

#import <string>
#import <vector>
#import "declaration.h"
#import "prototype.h"

class DeclarationInterface : Declaration{

	public:
		std::string userType;
		std::vector<Prototype> prototypes;
};

#endif