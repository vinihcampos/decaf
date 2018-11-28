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
			int label = Program::pc++;
			block1 = "if" + std::to_string(label);

			Program::d += "case(" + std::to_string(label) + "):\n";
			Program::d += "goto " + block1 + ";\n";

			code += "label = " + std::to_string(label) + ";\n";
			code += "if(eval) goto labels;\n";
			if(elseStatement != nullptr){
				label = Program::pc++;
				block2 = "else" + std::to_string(label);

				Program::d += "case(" + std::to_string(label) + "):\n";
				Program::d += "goto " + block2 + ";\n";

				code += "label = " + std::to_string(label) + ";\n";
				code += "if(!eval) goto labels;\n";
			}
			label = Program::pc++;
			int continueN = label;
			std::string continues = "continue" + std::to_string(label);

			Program::d += "case(" + std::to_string(label) + "):\n";
			Program::d += "goto " + continues + ";\n";

			code += "label = " + std::to_string(label) + ";\n";
			code += "goto labels;\n";
			
			code += block1 + ":{\n";
			code += ifStatement->generate() + "\n";

			code += "label = " + std::to_string(continueN) + ";\n";
			code += "goto labels;\n}\n";

			if(block2.compare("") != 0){
				code += block2 + ":{\n";
				code += elseStatement->generate() + "\n";
				code += "label = " + std::to_string(continueN) + ";\n";
				code += "goto labels;\n}\n";
			}

			code += continues + ":";

			return code;	
		}
};

#endif