#ifndef _RECURSIVE_
#define _RECURSIVE_

#include "token.h"

void prog();
void prog1();
void dec();
void dec1();
void var();
void type();
void type1();
void funcDec();
void formals();
void formals1();
void formals2();
void stmtBlock();
void stmtBlock1();
void statementList();
void stmt();
void conditionStmt();
void opTail();
void otherStmt();
void whileStmt();
void forStmt();
void returnStmt();
void breakStmt();
void printStmt();
void printOtherStmt();
void classDec();
void classDec1();
void classDec2();
void implements();
void field();
void interDec();
void prototype();
void exprAssign();
void exprAssignOrEmpty();
void expr();
void logicOp();
void relOp();
void relOp1();
void plusSubOp();
void plusSubOp1();
void mulDivModOp();
void mulDivModOp1();
void unaryOp();
void term();
void callOrVariable();
void call();
void callVariable();
void callAfterVariable();
void variableNotEmpty();
void callAfterVariable();
void variable();
void lValue();
void exprOrEmpty();
void exprSeq();
void actual();
void constant();

void error();
void eat(Token t);
void advance();

#endif