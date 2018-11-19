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
			std::cout << "{" ;
			for(int i = 0; i < declarations.size(); ++i){
				declarations[i]->toString();
				if(i + 1 < declarations.size())
					std::cout << ",";
				std::cout ;
			}
			std::cout << "}" ;

			std::cout << std::endl;
		}

		void generate(){

			std::cout << "#include <stdio.h>" << std::endl << std::endl;
			std::cout << "int main(){" << std::endl;

			for(int i = 0; i < declarations.size(); ++i){
				declarations[i]->generate();
			}
			
			std::cout << "\treturn 0;" << std::endl;
			std::cout << "}";
		}

};

#endif