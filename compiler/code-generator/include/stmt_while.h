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
			
			std::string block1;
			block1 = "while" + std::to_string(Program::pc++);
			std::string continues = "continue" + std::to_string(Program::pc++);
			code += "goto " + block1 + ";\n";
			code += continues + ":\n";

			Program::d += block1 + ":{\n";

			if(expression != nullptr){
				Program::d += "eval = ";
				Program::d += expression->generate();
				Program::d += ";\n";
			}else{
				Program::d += "eval = false;\n";
			}

			Program::d += "if(!eval) goto " + continues + ";\n";
			Program::d += whileStatement->generate() + "\n";
			Program::d += "goto " + block1 + ";\n}\n";

			return code;
		}
};

#endif