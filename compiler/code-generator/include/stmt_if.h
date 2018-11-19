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
			std::vector<std::string> formals;
			Frame f1("if" + std::to_string(Program::pc), Program::pc++, formals);
			Program::update_frames(f1);
			
			if(expression != nullptr){
				code += "eval = ";
				code += expression->generate();
				code += ";\n";
			}else{
				code += "eval = false;\n";
			}

			code += "pc = " + f1.id; 
			code += ";\n";
			code += "if(eval)\n";
			code += "goto d;\n";
			if(elseStatement != nullptr){
				Frame f2("else" + std::to_string(Program::pc), Program::pc++, formals); 
				Program::update_frames(f2);
				code += "pc = " + f2.id;
				code += ";\n";
				code += "goto d;\n";
			}
			return code;	
		}
};

#endif