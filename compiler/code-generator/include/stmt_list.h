#ifndef _STMT_LIST_
#define _STMT_LIST_

#include <string>
#include "stmt.h"

class StatementList{
	public:
		std::deque<Statement*> stmts;
		StatementList(std::deque<Statement*> stmts_) : stmts{stmts_} {}
		void toString(){
			std::cout << "[";
			if(stmts.size() > 0){
				for(int i = 0; i < stmts.size(); ++i){
					std::cout << "{";
					stmts[i]->toString();
					std::cout << "},";
				}
			}
			std::cout << "],";
		}

		std::string generate(){
			std::string code = "";
			for(int i = 0; i < stmts.size(); ++i){
				code += stmts[i]->generate() + "\n";
			}
			return code;
		}
};

#endif