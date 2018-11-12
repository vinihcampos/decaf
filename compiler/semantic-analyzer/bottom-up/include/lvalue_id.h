#ifndef _LVALUE_ID_
#define _LVALUE_ID_

#include <string>
#include "lvalue.h"

class LValueId : public LValue{

	public:
		std::string id;

		LValueId(std::string id_) : id{id_} {}
		void toString(){
			std::cout << "LValueId: {";
			std::cout << "id: " << id;
			std::cout << "}";
		}

};

#endif