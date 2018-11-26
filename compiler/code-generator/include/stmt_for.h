#ifndef _STMT_FOR_
#define _STMT_FOR_

#include <string>
#include "stmt.h"
#include "expression.h"
#include "stmt_expression.h"

class StatementFor : public Statement{
	
	public:
		StatementExpression * expression1;
		Expression * expression2;
		StatementExpression * expression3;
		Statement * forStatement;
		StatementFor(StatementExpression * expression1_, Expression * expression2_, 
					 StatementExpression * expression3_, Statement * forStatement_) :
			expression1{expression1_}, expression2{expression2_}, 
			expression3{expression3_}, forStatement{forStatement_} {}
		void toString(){
			std::cout << "StatementFor: {";
			if(expression1 != nullptr){
				std::cout << "condition1: "; 
				expression1->toString();
				std::cout << ",";
			}
			if(expression2 != nullptr){
				std::cout << "condition2: "; 
				expression2->toString();
				std::cout << ",";
			}
			if(expression3 != nullptr){
				std::cout << "condition3: "; 
				expression3->toString();
				std::cout << ",";
			}
			if(forStatement != nullptr){
				std::cout << "statement: ";
				forStatement->toString();
				std::cout << ",";
			}	
			std::cout << "}";
		}

		std::string generate() override{
			std::string code = "";

			if(expression1 != nullptr){
				code += expression1->generate();
			}

			std::string block1;
			block1 = "for" + std::to_string(Program::pc++);
			std::string continues = "continue" + std::to_string(Program::pc++);
			code += "goto " + block1 + ";\n";

			code += block1 + ":{\n";

			if(expression2 != nullptr){
				code += "eval = ";
				code += expression2->generate();
				code += ";\n";
			}else{
				code += "eval = false;\n";
			}

			code += "if(!eval) goto " + continues + ";\n";
			code += forStatement->generate() + "\n";

			if(expression3 != nullptr){
				code += expression3->generate();
			}

			code += "goto " + block1 + ";\n}\n";

			code += continues + ":\n";

			return code;
		}
};

#endif