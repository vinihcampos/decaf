#ifndef _DEC_CLASS_
#define _DEC_CLASS_

#include <string>
#include <deque>
#include <iostream>
#include "declaration.h"
#include "field.h"
#include "implements.h"
#include "static.h"

class DeclarationClass : public Declaration{

	public:
		std::string userType;
		std::string parent;
		Implements interfaces;
		Field fields;

		DeclarationClass(std::string userType_, std::string parent_, 
						 Implements interfaces_, Field fields_) : 
						 userType{userType_}, parent{parent_}, interfaces{interfaces_}, fields{fields_}{}

		void toString() override{
			std::cout << "DeclarationClass: {";
			std::cout << "userType: " << userType << ",";
			std::cout << "parent: " << parent << ",";
			std::cout << "Interfaces: ";
			interfaces.toString();
			std::cout << ",";
			fields.toString();
			std::cout << "}";
		}

		void tableGeneration(){

			for (int i = 0; i < fields.variables.size(); ++i){
				Symbol s;
				s.id = fields.variables[i]->id;
				s.type = fields.variables[i]->type;
				s.parent = userType;
				Static::table[userType + "_" + s.id] = s;
			}

			for (int i = 0; i < fields.functions.size(); ++i){
				Symbol s = fields.functions[i]->table();
				s.parent = userType;
				Static::table[userType + "_" + s.id] = s;
			}
		}

		std::string generate() override{
			std::string code = "";

			Static::currClass = userType;
			Static::structs += "struct " + userType + "{\n";
			for (int i = 0; i < fields.variables.size(); ++i){
				Static::structs += fields.variables[i]->generate() + "\n";
			}
			Static::structs += "};\n";

			for(int i = 0; i < fields.functions.size(); ++i){
				fields.functions[i]->generate();
			}
			Static::currClass = "";

			return code;
		}
};

#endif