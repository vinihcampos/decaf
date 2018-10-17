#ifndef _DEC_CLASS_
#define _DEC_CLASS_

#import <string>
#import <vector>
#import "declaration.h"
#import "field.h"

class DeclarationClass : Declaration{

	public:
		std::string userType;
		std::string parent;
		std::vector<std::string> interfaces;
		std::vector<Field> fields;
};

#endif