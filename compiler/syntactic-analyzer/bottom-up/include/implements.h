#ifndef _IMPLEMENTS_
#define _IMPLEMENTS_

#include <string>
#include <deque>	

class Implements{
	public:
		std::deque<std::string> implements;
		Implements(std::deque<std::string> implements_) : implements{implements_} {}
		void toString(){
			std::cout << "[";
			for(int i = 0; i < implements.size(); ++i){
				std::cout << implements[i] << ",";
			}
			std::cout << "]";
		}
};

#endif