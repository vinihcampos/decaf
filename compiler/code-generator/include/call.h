#ifndef _CALL_
#define _CALL_

#include <string>
#include "expression.h"
#include "expression_list.h"
#include "static.h"
#include "symbol.h"

class Call : public Expression{

	public:
		std::string id;
		Expression * expression1;
		ExpressionList actuals;

		Call(std::string id_, Expression * expression1_, ExpressionList actuals_) : 
			id{id_}, expression1{expression1_}, actuals{actuals_} {}

		void toString(){
			std::cout << "Call: {";
			if(expression1 != nullptr){
				std::cout << "leftExpression: ";
				expression1->toString();
				std::cout << ",";
			}
			std::cout << "id: " << id << ",";
			std::cout << "actuals: ";
			actuals.toString();
			std::cout << "}";
		}

		std::string generate() override{

			std::string exp = "";
			if(expression1 != nullptr){
				exp = expression1->generate();
			}

			int labelFun = Static::table[id].label;
			Symbol s = Static::table[id];

			int structId = Static::pc++;
			std::string structName = "fun_" + id + std::to_string(structId);
			Static::declarationFunctions += "fun_" + id + " " + structName + ";\n";

			std::string code = "";			
			for(int i = 0; i < actuals.expressions.size(); ++i){
				code += structName + "." + s.params[i] + " = " + actuals.expressions[i]->generate() + ";\n";
			}

			int label = Static::pc++;
			std::string continues = "continues" + std::to_string(label);
			Static::d += "case(" + std::to_string(label) + "):\n";
			Static::d += "goto " + continues + ";\n";

			code += structName + ".label = " + std::to_string(label) + ";\n";
			if(expression1 != nullptr) code += structName + ".attr = &" + exp + ";\n";
			code += "stack_fun_" + id + ".push(" + structName + ");\n"; 
			code += "label = " + std::to_string(labelFun) + ";\n";
			code += "goto labels;\n";
			code += continues + ":\n";

			return code;
		}

};

#endif