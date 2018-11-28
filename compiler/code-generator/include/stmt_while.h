#ifndef _STMT_WHILE_
#define _STMT_WHILE_

#include <string>
#include "stmt.h"
#include "expression.h"

class StatementWhile : public Statement{
	
	public:
		Expression * expression;
		Statement * whileStatement;
		StatementWhile(Expression * expression_, Statement * whileStatement_) :
			expression{expression_}, whileStatement{whileStatement_} {}
		void toString(){
			std::cout << "StatementWhile: {";
			if(expression != nullptr){
				std::cout << "condition: "; 
				expression->toString();
				std::cout << ",";
			}
			if(whileStatement != nullptr){
				std::cout << "statement: ";
				whileStatement->toString();
				std::cout << ",";
			}	
			std::cout << "}";
		}
		std::string generate() override{
			std::string code = "";
			
			int label = Program::pc++;
			int block1N = label;
			std::string block1;
			block1 = "while" + std::to_string(block1N);
			Program::d += "case(" + std::to_string(block1N) + "):\n";
			Program::d += "goto " + block1 + ";\n";

			int continueN = Program::pc++;
			std::string continues = "continue" + std::to_string(continueN);

			Program::d += "case(" + std::to_string(continueN) + "):\n";
			Program::d += "goto " + continues + ";\n";

			code += "label = " + std::to_string(block1N) + ";\n";
			code += "goto labels;\n";

			code += block1 + ":{\n";

			if(expression != nullptr){
				code += "eval = ";
				code += expression->generate();
				code += ";\n";
			}else{
				code += "eval = false;\n";
			}

			code += "label = " + std::to_string(continueN) + ";\n";
			code += "if(!eval) goto labels;\n";
			code += whileStatement->generate() + "\n";
			code += "label = " + std::to_string(block1N) + ";\n";
			code += "goto labels;\n}\n";

			code += continues + ":\n";

			return code;
		}
};

#endif