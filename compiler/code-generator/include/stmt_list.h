#ifndef _STMT_LIST_
#define _STMT_LIST_

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

		void generate(){
			for(int i = 0; i < stmts.size(); ++i){
				stmts[i]->generate();
			}
		}
};

#endif