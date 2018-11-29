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
				std::string structName = "fun_" + id;
				std::string structFunc = "struct " + structName + "{\n";
				structFunc += formals.generate();
				structFunc += "int label;\n";
				structFunc += "};\n";

				int label = Static::pc++;
				Static::d += "case(" + std::to_string(label) + "):\n";
				Static::d += "goto " + structName + ";\n";

				Static::funId[structName] = label;

				Static::structs += structFunc;
				Static::stacks += "stack<" + structName + "> stack_" + id + ";\n";
				Static::returns += type.generate() + " return_" + structName + ";\n";

				std::string code = "proc_" + id + ":{\n";

				code += structName + " " + structName + "_ = " + "stack_" + id + ".head();\n";

				for(int i = 0; i < formals.variables.size(); ++i){
					code += formals.variables[i].type.generate() + " " + formals.variables[i].id + " = " + structName + "_." + formals.variables[i].id + ";\n";
				}

				Static::currFun = type.base == VOID_T ? "" : structName;
				code += stmtBlock.generate();
				Static::currFun = "";

				code += "stack_" + id + ".pop();\n";
				code += "label = " + structName + "_.label;\n";
				code += "goto labels;\n";
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
			s.type = type;
			return s;
		}
};

#endif