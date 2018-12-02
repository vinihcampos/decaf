#ifndef _LVALUE_ID_
#define _LVALUE_ID_

#include <string>
#include "lvalue.h"
#include "static.h"

class LValueId : public LValue{

	public:
		std::string id;

		LValueId(std::string id_) : id{id_} {}
		void toString(){
			std::cout << "LValueId: {";
			std::cout << "id: " << id;
			std::cout << "}";
		}

		std::string generate() override{
			if(Static::currClass.compare("")){
				if(Static::table.find(Static::currClass + "_" + id) != Static::table.end())
					return "attr->" + id;
			}
			
			return id;
		}

};

#endif