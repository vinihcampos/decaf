#ifndef _INTERACTIVE_
#define _INTERACTIVE_

#include "token.h"
#include "table.h"
#include <string>
#include <vector>
#include <stack>

void error();
void eat(int t);
void advance();
void push_rule(std::vector<int>& regra, std::stack<int>& pilha);
void table_parser(std::stack<int>& pilha);
void imprime_pilha(std::stack<int>& pilha);

#endif