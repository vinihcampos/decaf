#ifndef _PROGRAM_
#define _PROGRAM_

#include <deque>
#include <string>
#include <iostream>
#include "declaration.h"

class Program{

	public:
		std::deque<Declaration*> declarations;
		void toString(){
			std::cout << "{" << std::endl;
			for(int i = 0; i < declarations.size(); ++i){
				declarations[i]->toString();
				if(i + 1 < declarations.size())
					std::cout << ",";
				std::cout << std::endl;
			}
			std::cout << "}" << std::endl;
		}

};

#endif