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
		std::string name;
		BaseType base;

		Type(){}
		Type(BaseType base_, int size_, std::string name_) : size{size_}, base{base_} , name{name_}{}

		void toString(){
			std::cout << "type: {";
			std::cout << "base: " << baseTypeToString() << "," ;
			std::cout << "size: " << size ;
			std::cout << "}";
		}

		std::string generate(){
			std::string pointers = "";
			for(int i = 0; i < size; ++i)
				pointers += "*";
			return baseTypeToCType() + pointers;
		}

		std::string baseTypeToString(){
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

		std::string baseTypeToCType(){
			switch(base){
				case INT_T:
					return "int";
				case DOUBLE_T:
					return "double";
				case BOOL_T:
					return "bool";
				case STRING_T:
					return "string";
				case USERTYPE_T:
					return name;
				case VOID_T :
					return "void";
				default:
					return "ERROR";
			}
		}

};

#endif