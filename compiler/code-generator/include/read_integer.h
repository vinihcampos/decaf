#ifndef _READ_INTEGER_
#define _READ_INTEGER_

#include "expression.h"

class ReadInteger : public Expression{
	public:
		void toString(){
			std::cout << "ReadInteger()";
		}

		std::string generate(){
			return "";
		}
};

#endif