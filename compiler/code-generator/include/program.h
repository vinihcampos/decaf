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

class Program{

	public:
		std::deque<Declaration*> declarations;
		static int pc;
		static std::string d;
		static std::string structs;
		static std::string blocks;
		static std::string stacks;
		static std::map<std::string, Symbol> table;
		
		Program(){
			pc = 0;
			d = "labels: \nswitch(label){\n";
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
			code += "#include <string>\n\n";
			code += "using namespace std;\n\n";

			code += "int pc = 0;\n";
			code += "int label;\n";
			code += "bool eval = false;\n";
			code += "int readIntAux;\n";
			code += "std::string readStringAux;\n\n";

			code += "int main(){\n";

			for(int i = 0; i < declarations.size(); ++i){
				code += declarations[i]->generate();
			}

			d += "default:\n";
			d += "return 0;\n}\n";

			code += "return 0;\n";
			code += d + "\n";
			code += "}";

			return code;
		}

		void tableGeneration(){
			for(int i = 0; i < declarations.size(); ++i){
				if (DeclarationFunction* t = dynamic_cast<DeclarationFunction*>(declarations[i])){
					Symbol s = t->table();
					s.parent = "_GLOBAL_";
					table[s.id] = s;
				}
			}			
		}

		void tablePrint(){
			for (auto& kv : table) {
			    std::cout << kv.first << ": ";
			    for(int i = 0; i < kv.second.params.size(); ++i){
			    	std:: cout << kv.second.params[i] << ",";
			    }
			    std::cout << std::endl;
			}
		}

		static void update_frames(Frame f){
			d += "\tcase " + std::to_string(f.id) + ":\n";
			d += "\t\tgoto " + f.label + ";\n";
			d += "\t\tbreak;\n";
		}



};

#endif