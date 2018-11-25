#ifndef _STMT_IF_
#define _STMT_IF_

#include "stmt.h"
#include "expression.h"
#include "frame.h"
#include "program.h"
#include <iostream>
#include <string>

class StatementIf : public Statement{
	
	public:
		Expression * expression;
		Statement * ifStatement;
		Statement * elseStatement;
		StatementIf(Expression * expression_, Statement * ifStatement_, Statement * elseStatement_) :
			expression{expression_}, ifStatement{ifStatement_}, elseStatement{elseStatement_} {}
		void toString(){
			std::cout << "StatementIf: {";
			if(expression != nullptr){
				std::cout << "condition: "; 
				expression->toString();
				std::cout << ",";
			}
			if(ifStatement != nullptr){
				std::cout << "statement: ";
				ifStatement->toString();
				std::cout << ",";
			}			
			if(elseStatement != nullptr){
				std::cout << "elseStatement: ";
				elseStatement->toString();
				std::cout << ",";
			}
			std::cout << "}";
		}

		std::string generate() override{
			std::string code = "";
			
			if(expression != nullptr){
				code += "eval = ";
				code += expression->generate();
				code += ";\n";
			}else{
				code += "eval = false;\n";
			}

			std::string block1;
			std::string block2 = ""; 
			block1 = "if" + std::to_string(Program::pc++);
			code += "if(eval) goto " + block1 + ";\n";
			if(elseStatement != nullptr){
				block2 = "else" + std::to_string(Program::pc++);
				code += "if(!eval) goto " + block2 + ";\n";
			}

			std::string continues = "continue" + std::to_string(Program::pc++);

			code += continues + ":\n";

			Program::d += block1 + ":{\n";
			Program::d += ifStatement->generate() + "\n";
			Program::d += "goto " + continues + ";\n}";

			if(block2.compare("") != 0){
				Program::d += block2 + ":{\n";
				Program::d += elseStatement->generate() + "\n";
				Program::d += "goto " + continues + ";\n}\n";
			}

			return code;	
		}
};

#endif