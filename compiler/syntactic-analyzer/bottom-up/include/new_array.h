#ifndef _NEW_ARRAY_
#define _NEW_ARRAY_

#include "expression.h"
#include "type.h"

class NewArray : public Expression{

	public:
		Type type;
		Expression * expression;
		NewArray(Type type_, Expression * expression_) : type{type_}, expression{expression_} {}
		void toString(){
			std::cout << "NewArray: {";
			if(expression != nullptr){
				std::cout << "expression: ";
				expression->toString();
				std::cout << ",";
			}
			type.toString();
			std::cout << "}";
		}
};

#endif