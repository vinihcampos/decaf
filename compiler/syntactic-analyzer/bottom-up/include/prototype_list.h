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
			
		}

};

#endif