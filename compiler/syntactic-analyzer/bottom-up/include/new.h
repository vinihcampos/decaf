#ifndef _NEW_
#define _NEW_

#include <string>
#include "expression.h"

class New : public Expression{
	public:
		std::string userType;
		New(std::string userType_) : userType{userType_} {}
		void toString(){
			std::cout << "New: {";
			std::cout << "userType: " << userType;
			std::cout << "}";
		}
};

#endif