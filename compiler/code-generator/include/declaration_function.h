#ifndef _DEC_FUNCTION_
#define _DEC_FUNCTION_

#include <string>
#include <vector>
#include <iostream>
#include "declaration.h"
#include "type.h"
#include "formal.h"
#include "stmt_block.h"
#include "static.h"

class DeclarationFunction : public Declaration{

	public:
		Type type;
		std::string id;
		Formal formals;
		StatementBlock stmtBlock;

		DeclarationFunction(Type type_, std::string id_, Formal formals_, StatementBlock stmtBlock_) : 
		type{type_}, id{id_}, formals{formals_}, stmtBlock{stmtBlock_}{}
		
		void toString() override{
			std::cout << "DeclarationFunction: { " ;
			std::cout << "id: " << id << "," ;
			type.toString();
			std::cout << "," ;
			std::cout << "formals: "; formals.toString();
			std::cout << "," ;
			std::cout << "StatementBlock: "; stmtBlock.toString();
			std::cout << "}";
		}

		std::string generate(){
			if(id.compare("main") == 0)
				return stmtBlock.generate();
			else{
				std::string structName = "fun" + id;
				std::string structFunc = "struct " + structName + "{\n";
				structFunc += formals.generate();
				structFunc += "int label;\n";
				structFunc += "};\n";

				Static::structs += structFunc;
				Static::stacks += "stack<" + structName + "> stack" + id + ";\n";

				std::string code = "proc_" + id + ":{\n";

				code += structName + " " + structName + "_ = " + "stack" + id + ".head();\n";

				for(int i = 0; i < formals.variables.size(); ++i){
					code += formals.variables[i].type.generate() + " " + formals.variables[i].id + " = " + structName + "_." + formals.variables[i].id + ";\n";
				}

				code += stmtBlock.generate();
				code += "stack" + id + ".pop();\n";
				code += "}\n";

				Static::blocks += code;
				return "";
			}
		}

		Symbol table(){
			Symbol s; std::vector<std::string> parameters;
			for(int i = 0; i < formals.variables.size(); ++i){
				parameters.push_back(formals.variables[i].id);
			}
			s.id = id;
			s.params = parameters;
			return s;
		}
};

#endif