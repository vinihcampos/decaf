#ifndef _PROGRAM_
#define _PROGRAM_

#include <deque>
#include <string>
#include "declaration.h"

class Program{

	public:
		std::deque<Declaration*> declarations;

};

#endif