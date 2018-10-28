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

};

#endif