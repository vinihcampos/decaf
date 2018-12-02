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
				std::string structName; 
				//if(!Static::currClass.compare(""))
					structName = "fun_" + id;
				//else
				//	structName = "method_" + id;
				std::string structFunc = "struct " + structName + "{\n";
				structFunc += formals.generate();
				structFunc += "int label;\n";

				if(Static::currClass.compare(""))
					structFunc += Static::currClass + " * attr;\n"; 

				structFunc += "};\n";

				int label = Static::table[id].label;
				Static::d += "case(" + std::to_string(label) + "):\n";
				Static::d += "goto label_" + structName + ";\n";

				Static::funId[structName] = label;

				Static::structs += structFunc;
				Static::stacks += "stack<" + structName + "> stack_" + structName + ";\n";
				if(type.base != VOID_T)
					Static::returns += type.generate() + " return_" + structName + ";\n";

				std::string code = "label_" + structName + ":{\n";

				Static::declarationFunctions += structName + " " + structName + "_;\n";
				code += structName + "_ = " + "stack_" + structName + ".top();\n";

				for(int i = 0; i < formals.variables.size(); ++i){
					code += formals.variables[i].type.generate() + " " + formals.variables[i].id + ";\n";
					code += formals.variables[i].id + " = " + structName + "_." + formals.variables[i].id + ";\n";
				}

				if(Static::currClass.compare("")){
					code += Static::currClass + " * attr;\n";
					code += "attr = " + structName + "_.attr;\n";
				}

				Static::currFun = type.base == VOID_T ? "-" + structName : structName;
				code += stmtBlock.generate();

				if(type.base == VOID_T){
					std::string name = Static::currFun.substr(1, Static::currFun.size() - 1);
					code += "\n" + name + " auxReturn = stack_" + name + ".top();\n";
					code += "stack_" + name + ".pop();\n";
					code += "label = auxReturn.label;\n";
					code += "goto labels;\n";
				}

				Static::currFun = "";

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
			s.label = Static::pc++;
			return s;
		}
};

#endif