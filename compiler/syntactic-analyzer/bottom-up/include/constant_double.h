#ifndef _DOUBLE_CONSTANT_
#define _DOUBLE_CONSTANT_

#include "constant.h"

class DoubleConstant : public Constant {
	public:
		double value;

		DoubleConstant(double value_) : value{value_} {}
		void toString(){
			
		}
};

#endif