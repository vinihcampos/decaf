#include <iostream>
#include <string>
#include "token.h"
#include "table_parser.h"
#include <map>

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
		if(top < Prog) { 
			eat(top);
			pilha.pop();
		}
		else {
			std::pair <int,int> product1;
			product1.first = top;
			product1.second = tok;   
			 
			if(table.find(product1) != table.end()) { 
				pilha.pop();
				push_rule(table[product1], pilha);
			}
			else {
				error();
			}
		}
	}

}

void eat(int t){
    if(t == tok){
        advance();
    }else{
        error();
   }
}

void error(){
	cout << "Deu erro, amigo\n";
}

void push_rule(std::vector<int>& regra, std::stack<int>& pilha) {
	for(int i = regra.size()-1; i >= 0; i--) {
		pilha.push(regra[i]);
	}
}