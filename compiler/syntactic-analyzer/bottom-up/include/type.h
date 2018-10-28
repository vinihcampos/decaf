#ifndef _TYPE_
#define _TYPE_

enum BaseType{
	INT,
	DOUBLE,
	BOOL,
	STRING,
	USERTYPE,
	VOID
};

class Type{
	
	public:
		int size;
		BaseType type;

};

#endif