#ifndef _STMT_IF_
#define _STMT_IF_

#include "stmt.h"
#include "expression.h"
#include "frame.h"
#include "program.h"
#include <iostream>

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

		void generate() override{
			std::vector<std::string> formals;
			Frame f1("if" + std::to_string(Program::pc), Program::pc++, formals);
			Program::update_frames(f1);
			
			if(expression != nullptr){
				std::cout << "eval = ";
				expression->generate();
				std::cout << ";" << std::endl;
			}else{
				std::cout << "eval = false;";
			}

			std::cout << "pc = " << f1.id << ";" << std::endl;
			std::cout << "if(eval)" << std::endl;
			std::cout << "goto d;" << std::endl;
			if(elseStatement != nullptr){
				Frame f2("else" + std::to_string(Program::pc), Program::pc++, formals); 
				Program::update_frames(f2);
				std::cout << "pc = " << f2.id << ";" << std::endl;
				std::cout << "goto d;" << std::endl;
			}			
		}
};

#endif