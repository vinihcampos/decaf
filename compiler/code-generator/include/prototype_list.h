#ifndef _DEC_PROTOTYPE_LIST_
#define _DEC_PROTOTYPE_LIST_

#include <string>
#include "prototype.h"

class PrototypeList{

	public:
		std::deque<Prototype> prototypes;

		PrototypeList(std::deque<Prototype> prototypes_) :
			prototypes{prototypes_}{}
		void toString(){
			std::cout << "[";
			for(int i = 0; i < prototypes.size(); ++i){
				prototypes[i].toString();
				std::cout << ",";
			}
			std::cout << "]";
		}

};

#endif