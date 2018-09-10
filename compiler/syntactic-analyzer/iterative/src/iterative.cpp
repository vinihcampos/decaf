#include <iostream>
#include <string>
#include "token.h"
#include "iterative.h"
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
	//imprime_pilha(pilha);
	while(!pilha.empty()) {
		int top = pilha.top();
		if(top < Prog) { 
			eat(top);
			pilha.pop();
			//imprime_pilha(pilha);
		}
		else {
			std::pair <int,int> product1;
			product1.first = top;
			product1.second = tok;   
			 
			if(table.find(product1) != table.end()) { 
				pilha.pop();
				push_rule(table[product1], pilha);
				//imprime_pilha(pilha);
			}
			else {
				error(top, tok, 1);
				break;
			}
		}
	}

}

void imprime_pilha(stack<int>& pilha){
	stack<int> temp = pilha;
	while (!temp.empty())
	{
		cout << temp.top() << " ";
		temp.pop();
	}
	cout << "\n";
}

void eat(int t){
    if(t == tok){
        advance();
    }else{
        error(t, tok);
   }
}

void error(int t, int tt){
	cout << "esperava " << tt << ", mas veio " << t << "\n";
}
void error(int rule, int t, int a){
	cout << "Não achou: " << rule << ", " << t << "\n";
}

void push_rule(std::vector<int>& regra, std::stack<int>& pilha) {
	for(int i = regra.size()-1; i >= 0; i--) {
		pilha.push(regra[i]);
	}
}