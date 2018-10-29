#ifndef _BOOL_CONSTANT_
#define _BOOL_CONSTANT_

#include "constant.h"

class BoolConstant : public Constant {
	public:
		bool value;
		BoolConstant(bool value_) : value{value_} {}
		void toString(){
			
		}
};

#endif