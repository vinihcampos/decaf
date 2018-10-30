#ifndef _TYPE_
#define _TYPE_

#include <iostream>
#include <string>

enum BaseType{
	INT_T,
	DOUBLE_T,
	BOOL_T,
	STRING_T,
	USERTYPE_T,
	VOID_T
};

class Type{
	
	public:
		int size;
		BaseType base;

		Type();
		Type(BaseType base_, int size_) : size{size_}, base{base_} {}

		void toString(){
			std::cout << "type: {";
			std::cout << "base: " << BaseTypeToString() << "," ;
			std::cout << "size: " << size ;
			std::cout << "}";
		}

		std::string BaseTypeToString(){
			switch(base){
				case INT_T:
					return "INT";
				case DOUBLE_T:
					return "DOUBLE";
				case BOOL_T:
					return "BOOL";
				case STRING_T:
					return "STRING";
				case USERTYPE_T:
					return "USERTYPE";
				case VOID_T :
					return "VOID";
				default:
					return "ERROR";
			}
		}

};

#endif