#ifndef _PROGRAM_
#define _PROGRAM_

#include <deque>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include "declaration.h"
#include "declaration_function.h"
#include "frame.h"
#include "symbol.h"
#include "static.h"

class Program{

	public:
		std::deque<Declaration*> declarations;
		
		Program(){
			Static::pc = 0;
			Static::d = "labels:{\nswitch(label){\n";
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
			code += "#include <iostream>\n";
			code += "#include <stack>\n";
			code += "#include <string>\n\n";
			code += "using namespace std;\n";

			std::string remainCode = "";

			remainCode += "\n// Auxiliar variables";
			remainCode += "int pc = 0;\n";
			remainCode += "int label;\n";
			remainCode += "bool eval = false;\n";
			remainCode += "int readIntAux;\n";
			remainCode += "std::string readStringAux;\n\n";

			remainCode += "int main(){\n";

			for(int i = 0; i < declarations.size(); ++i){
				remainCode += declarations[i]->generate();
			}

			Static::d += "default:\n";
			Static::d += "return 0;\n}\n";

			remainCode += "return 0;\n";
			remainCode += Static::blocks;
			remainCode += Static::d + "\n";
			remainCode += "}\n}\n";

			code += "\n// Structs' definitions\n";
			code += Static::structs;
			code += "\n// Stacks' definitions\n";
			code += Static::stacks;
			code += "\n// Returns' definitions\n";
			code += Static::returns;
			code += remainCode;

			return code;
		}

		void tableGeneration(){
			for(int i = 0; i < declarations.size(); ++i){
				if (DeclarationFunction* t = dynamic_cast<DeclarationFunction*>(declarations[i])){
					Symbol s = t->table();
					s.parent = "_GLOBAL_";
					Static::table[s.id] = s;
				}
			}			
		}

		void tablePrint(){
			for (auto& kv : Static::table) {
			    std::cout << kv.first << ": ";
			    for(int i = 0; i < kv.second.params.size(); ++i){
			    	std:: cout << kv.second.params[i] << ",";
			    }
			    std::cout << "/ label: " << kv.second.label;
			    std::cout << std::endl;
			}
		}
};

#endif