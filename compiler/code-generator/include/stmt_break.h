#ifndef _STMT_BREAK_
#define _STMT_BREAK_

#include <string>

#include "stmt.h"


class StatementBreak : public Statement{
	public:
		void toString(){
			std::cout << "StatementBreak: { break }";
		}

		std::string generate() override{
			return "";
		}
};

#endif