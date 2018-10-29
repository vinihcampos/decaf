#ifndef _INT_CONSTANT_
#define _INT_CONSTANT_

#include "constant.h"

class IntConstant : public Constant {
	public:
		int value;
		IntConstant(int value_) : value{value_} {}
		void toString(){
			
		}
};

#endif