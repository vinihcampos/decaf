#ifndef _DEC_PROTOTYPE_
#define _DEC_PROTOTYPE_

#import <string>
#import "type.h"
#import "formal.h"

class Prototype{

	public:
		Type type;
		std::string id;
		Formal formals;

};

#endif