// #include <iostream>
// #include <string>
// #include "recursive.h"
// #include "token.h"
#include "table_parser.h"

using namespace std;

extern FILE* yyin;
extern int yylex();
extern int row, column;
extern int tok;
extern char * lexema;

int main(int argc, char** args){
    if(argc > 1){
    	yyin = fopen(args[1], "r");
        advance();
        init_table();
        stack<int> pilha;
        pilha.push(Prog);
		table_parser(pilha);
    }
    return 0;
}

void advance(){
    yylex();
}

void table_parser(stack<int>& pilha) {
	while(!pilha.empty()) {
		int top = pilha.top();
		if(top < PROGRAM) { 
			eat(top);
			pilha.pop();
		}
		else {
			if(table.find({top, tok}) == table.end()) { 
				error();
			}
			else {
				pilha.pop();
				push_rule(table[{top, tok}], pilha);
			}
		}
	}

}

void eat(Token t){
    if(t == tok){
        advance();
    }else{
        error();
   }
}

void error(){
	cout << "Deu erro, amigo" << endl;
}

void push_rule(std::vector<int>& regra, std::stack<int>& pilha) {
	for(int i = regra.size()-1; i >= 0; i--) {
		pilha.push(regra[i]);
	}
}