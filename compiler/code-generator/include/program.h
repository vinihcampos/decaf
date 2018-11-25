#ifndef _PROGRAM_
#define _PROGRAM_

#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include "declaration.h"
#include "frame.h"

class Program{

	public:
		std::deque<Declaration*> declarations;
		static int pc;
		static std::string d;
		static std::vector<std::string> blocks;
		
		Program(){
			pc = 0;
		}	

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

		std::string generate(){
			std::string code = "";
			code += "#include <cstdio>\n";
			code += "#include <string>\n\n";
			code += "using namespace std;\n\n";
			code += "int main(){\n";
			code += "int pc = 0;\n";
			code += "bool eval = false;\n";

			for(int i = 0; i < declarations.size(); ++i){
				code += declarations[i]->generate();
			}

			code += "\treturn 0;\n";
			code += d + "\n";
			code += "}";

			return code;
		}

		static void update_frames(Frame f){
			d += "\tcase " + std::to_string(f.id) + ":\n";
			d += "\t\tgoto " + f.label + ";\n";
			d += "\t\tbreak;\n";
		}

};

#endif