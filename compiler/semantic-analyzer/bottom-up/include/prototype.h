#ifndef _DEC_PROTOTYPE_
#define _DEC_PROTOTYPE_

#include <string>
#include "type.h"
#include "formal.h"

class Prototype{

	public:
		Type type;
		std::string id;
		Formal formals;

		Prototype(Type type_, std::string id_, Formal formals_) :
			type{type_}, id{id_}, formals{formals_}{}
		void toString(){
			std::cout << "{";
			type.toString();
			std::cout << ", id: " << id << ",";
			formals.toString();
			std::cout << "}";
		}

};

#endif