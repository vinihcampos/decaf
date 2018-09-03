#include <iostream>
#include <string>
#include "recursive.h"

using namespace std;

extern FILE* yyin;
extern int yylex();
extern int column, row;
extern Token tok;

string getTokenString(Token token){
    switch(token){
	case tVoid:
	    return "T_VOID";
        case tInt:
            return "T_INT";           
        case tDouble:
            return "T_DOUBLE";        
        case tBool:
            return "T_BOOL";          
        case tString:
            return "T_STRING";        
        case tClass:
            return "T_CLASS";         
        case tInterface:
            return "T_INTERFACE";     
        case tNull:
            return "T_NULL";          
        case tThis:
            return "T_THIS";       
        case tExtends:
            return "T_EXTENDS";       
        case tImplements:
            return "T_IMPLEMENTS";    
        case tFor:
            return "T_FOR";           
        case tWhile:
            return "T_WHILE";         
        case tIf:
            return "T_IF";            
        case tElse:
            return "T_ELSE";          
        case tReturn:;
            return "T_RETURN";        
        case tBreak:
            return "T_BREAK";         
        case tNew:
            return "T_NEW";           
        case tNewArray:
            return "T_NEW_ARRAY";      
        case tPrint:
            return "T_PRINT";         
        case tReadInteger:
            return "T_READ_INTEGER";   
        case tReadLine:
            return "T_READ_LINE";      
        case tId:
            return "T_ID";
        case tUserType:
            return "T_USER_TYPE";            
        case tPlus:
            return "T_+";
        case tMinus:
            return "T_-";
        case tMulti:
            return "T_*";
        case tDiv:
            return "T_/";
        case tMod:
            return "T_\%";
        case tLess:
            return "T_<";
        case tLessEqual:
            return "T_<=";
        case tGreater:
            return "T_>";
        case tGreaterEqual:
            return "T_>=";
        case tEqual:
            return "T_==";
        case tDiff:
            return "T_!=";
        case tAssignment:
            return "T_=";
        case tAnd:
            return "T_&&";
        case tOr:
            return "T_||";
        case tNot:
            return "T_!";
        case tSemiColon:
            return "T_;";
        case tComma:
            return "T_,";
        case tDot:
            return "T_.";
        case tBracketLeft:
            return "T_[";
        case tBracketRight:
            return "T_]";
        case tParLeft:
            return "T_(";
        case tParRight:
            return "T_)";  
        case tBraceLeft:
            return "T_{";
        case tBraceRight:
            return "T_}";
        case tIntConstant:
            return "T_INT_CONST";
        case tDoubleConstant:
            return "T_DOUBLE_CONST";
        case tTrue:
            return "T_TRUE";
        case tFalse:
            return "T_FALSE";
        case tStringConstant:
            return "T_STRING_CONST";
        case tEOF:
            return "T_END_OF_FILE";
		default:
			return "T_ERROR";
    }
}


void prog(){
    switch(tok){
        case tEOF:
            break;
        default:
            dec(); prog1();
            break;
    }
    
}

void prog1(){
    prog();
}

void dec(){
    switch(tok){
        case tClass:
            classDec();
            break;
        case tInterface:
            interDec();
            break;
        case tVoid:
            eat(tVoid); eat(tId); funcDec();
            break;
        default:
            var(); dec1();
            break;
    }
}

void dec1(){
    switch(tok){
        case tSemiColon:
            eat(tSemiColon);
            break;
        default:
            funcDec();
            break;
    }
}

void var(){
    type(); eat(tId);        
}

void type(){
    switch(tok){
        case tInt:
            eat(tInt); type1();
            break;
        case tDouble:
            eat(tDouble); type1();
            break;
        case tBool:
            eat(tBool); type1();
            break;
        case tString:
            eat(tString); type1();
            break;
        case tUserType:
            eat(tUserType); type1();
            break;
        default:
            error();
            break;
    }
}

void type1(){
    switch(tok){
        case tId:
            break;
        case tBracketLeft:
            eat(tBracketLeft); eat(tBracketRight); type1();
            break;
        default:
            error();
            break;
    }
}

void funcDec(){
    switch(tok){
        case tParLeft:
            eat(tParLeft); formals(); eat(tParRight); stmtBlock();
            break;
        default:
            error();
            break;
    }
}

void formals(){
    switch(tok){
        case tParRight:
            break;
        default:
            formals1();
            break;
    }
}

void formals1(){
    var(); formals2();
}

void formals2(){
    switch(tok){
        case tParRight:
            break;
        case tComma:
            eat(tComma); formals1();
            break;
        default:
            error();
            break;        
    }
}

void stmtBlock(){
    switch(tok){
        case tBraceLeft:
            eat(tBraceLeft); stmtBlock1(); eat(tBraceRight);
            break;
        default:
            error();
            break;
    }
}

void stmtBlock1(){
    switch(tok){
        case tInt:
        case tDouble:
        case tBool:
        case tString:
        case tUserType:
            var(); eat(tSemiColon); stmtBlock1();
            break;
        default:
            statementList();
            break;
    }
}

void statementList(){
    switch(tok){
        case tBraceRight:
            break;
        default:
            stmt(); statementList();
            break;
    }
}

void stmt(){
    switch(tok){
        case tIf:
            conditionStmt();
            break;
        default:
            otherStmt();
            break;
    }
}

void conditionStmt(){
    switch(tok){
        case tIf:
            eat(tIf); eat(tParLeft); expr(); eat(tParRight); stmtBlock(); opTail();
            break;
        default:
            error();
            break;
    }
}

void opTail(){
    switch(tok){
        case tElse:
            eat(tElse); stmtBlock();
        case tBraceRight:
            break;
        default:
            error();
    }
}

void otherStmt(){
    switch(tok){
        case tWhile:
            whileStmt();
            break;
        case tFor:
            forStmt();
            break;
        case tBreak:
            breakStmt();
            break;
        case tReturn:
            returnStmt();
            break;
        case tPrint:
            printStmt();
            break;
        case tBraceLeft:
            stmtBlock();
            break;
        case tId:
        case tThis:
            exprAssign(); eat(tSemiColon);
            break;
        case tSemiColon:
            eat(tSemiColon);
            break;
        default:
            error();
            break;
    }
}

void whileStmt(){
    switch(tok){
        case tWhile:
            eat(tWhile); eat(tParLeft); expr(); eat(tParRight); stmt();
            break;
        default:
            error();
            break;
    }
}

void forStmt(){
    switch(tok){
        case tFor:
            eat(tFor); eat(tParLeft); exprAssignOrEmpty(); eat(tSemiColon); expr(); eat(tSemiColon); exprOrEmpty(); eat(tParRight); stmt();
            break;
        default:
            error();
            break;
    }
}

void returnStmt(){
    switch(tok){
        case tReturn:
            eat(tReturn); exprOrEmpty(); eat(tSemiColon);
            break;
        default:
            error();
            break;
    }
}

void breakStmt(){
    switch(tok){
        case tBreak:
            eat(tBreak); eat(tSemiColon);
            break;
        default:
            error();
            break;
    }
}

void printStmt(){
    switch(tok){
        case tPrint:
            eat(tPrint); eat(tParLeft); expr(); printOtherStmt();
            break;
        default:
            error();
            break;
    }
}

void printOtherStmt(){
    switch(tok){
        case tParRight:
            eat(tParRight); eat(tSemiColon);
            break;
        case tComma:
            eat(tComma); expr(); printOtherStmt();
        default:
            error();
            break;
    }
}

void classDec(){
    switch(tok){
        case tClass:
            eat(tClass); eat(tUserType); classDec1();
            break;
        default:
            error();
            break;
    }
}

void classDec1(){
    switch(tok){
        case tExtends:
            eat(tExtends); eat(tUserType); classDec2();
            break;
        default:
            classDec2();
            break;
    }
}

void classDec2(){
    switch(tok){
        case tImplements:
            eat(tImplements); eat(tUserType); implements(); eat(tBraceLeft); field(); eat(tBraceRight);
            break;
        case tBraceLeft:
            eat(tBraceLeft); field(); eat(tBraceRight);
            break;
        default:
            error();
            break;
    }
}

void implements(){
    switch(tok){
        case tBraceLeft:
            break;
        case tComma:
            eat(tComma); eat(tUserType); implements();
            break;
        default:
            error();
    }
}

void field(){
    switch(tok){
        case tBraceRight:
            break;
        default:
            var(); dec1(); field();
            break;
    }
}

void interDec(){
    switch(tok){
        case tInterface:
            eat(tInterface); eat(tUserType); eat(tBraceLeft); prototype(); eat(tBraceRight);
            break;
        default:
            error();
            break;
    }
}

void prototype(){
    switch(tok){
        case tBraceRight:
            break;
        case tVoid:
            eat(tVoid); eat(tId); eat(tParLeft); formals(); eat(tParRight); eat(tSemiColon);
            break;
        default:
            var(); eat(tParLeft); formals(); eat(tParRight); eat(tSemiColon);
    }
}

void expr(){
    relOp(); logicOp();
}

void logicOp(){
    switch(tok){
        case tOr:
            eat(tOr); relOp(); logicOp();
            break;
        case tAnd:
            eat(tAnd); relOp(); logicOp();
            break;
        case tParRight:
        case tSemiColon:
        case tPrint:
        case tComma:
        case tBracketRight:
            break;
        default:
            error();
            break;
    }
}

void relOp(){
    plusSubOp(); relOp1();
}

void exprAssign(){
    lValue(); variable(); 
    switch(tok){
        case tAssignment:
            eat(tAssignment); expr();
            break;
        default:
            error();
            break;
    }
}

void exprAssignOrEmpty(){
    switch(tok){
        case tSemiColon:
            break;
        default:
            exprAssign();
            break;
    }
}

void variable(){
    switch(tok){
        case tAssignment:
        case tMulti:
        case tDiv:
        case tMod:
        case tPlus:
        case tMinus:
        case tLess:
        case tLessEqual:
        case tGreater:
        case tGreaterEqual:
        case tEqual:
        case tDiff:
        case tOr:
        case tAnd:
        case tParRight:
        case tSemiColon:
        case tComma:
            break;
        case tBracketLeft:
            eat(tBracketLeft); expr(); eat(tBraceRight); variable();
            break;
        case tDot:
            eat(tDot); lValue(); variable();
            break;
        default:
            error();
            break;
    }
}

void lValue(){
    switch(tok){
        case tId:
            eat(tId);
            break;
        case tThis:
            eat(tThis); eat(tDot); eat(tId);
            break;
        default:
            error();
            break;
    }
}

void exprOrEmpty(){
    switch(tok){
        case tSemiColon:
            break;
        default:
            expr();
            break;
    }
}

int main(int argc, char** args){
    if(argc > 1){
    	yyin = fopen(args[1], "r");
        advance();
        prog();
    }else{
    	error();
    }
    return 0;
}

void error(){
    fprintf(stderr, "An error was found\n");
}

void advance(){
    yylex();
}

void eat(Token t){
    if(t == tok){
        advance();
    }else{
        error();
    }
}