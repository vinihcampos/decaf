#ifndef _DECLARATION_
#define _DECLARATION_

#include <iostream>

class Declaration{
	public:
		virtual void toString(){
			std::cout << "Declaration" << std::endl;
		}
};

#endif