#include <iostream>
#include <string>
#include "recursive.h"
#include "token.h"

using namespace std;

extern FILE* yyin;
extern int yylex();
extern int row, column;
extern Token tok;
extern char * lexema;

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
            vector<Token> tokens = {tInt,tDouble,tBool,tString,tUserType};
            error(tokens);
            break;
    }
}

void type1(){
    switch(tok){
        case tBracketLeft:
            eat(tBracketLeft); eat(tBracketRight); type1();
            break;        
        default:
            break;
    }
}

void funcDec(){
    switch(tok){
        case tParLeft:
            eat(tParLeft); formals(); eat(tParRight); stmtBlock();
            break;
        default:
            vector<Token> tokens = {tParLeft};
            error(tokens);
            break;
    }
}

void formals(){
    switch(tok){
        case tInt:
        case tDouble:
        case tBool:
        case tString:
        case tUserType:
            formals1();
            break;
        default:
            break;
    }
}

void formals1(){
    var(); formals2();
}

void formals2(){
    switch(tok){
       case tComma:
            eat(tComma); formals1();
            break;
        default:
            break;        
    }
}

void stmtBlock(){
    switch(tok){
        case tBraceLeft:
            eat(tBraceLeft); stmtBlock1(); eat(tBraceRight);
            break;
        default:
            vector<Token> tokens = {tBraceLeft};
            error(tokens);
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
        case tIf:
        case tSemiColon:
        case tWhile:
        case tFor:
        case tBreak:
        case tReturn:
        case tPrint:
        case tBraceLeft:
        case tId:
        case tThis: 
            stmt(); statementList();
            break;
        default:
            break;
    }
}

void stmt(){
    switch(tok){
        case tIf:
            conditionStmt();
            break;
        case tSemiColon:
        case tWhile:
        case tFor:
        case tBreak:
        case tReturn:
        case tPrint:
        case tBraceLeft:
        case tId:
        case tThis:
            otherStmt();
            break;
        default:
            vector<Token> tokens = {tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis};
            error(tokens);
            break;
    }
}

void conditionStmt(){
    switch(tok){
        case tIf:
            eat(tIf); eat(tParLeft); expr(); eat(tParRight); stmtBlock(); opTail();
            break;
        default:
            vector<Token> tokens = {tIf};
            error(tokens);
            break;
    }
}

void opTail(){
    switch(tok){
        case tElse:
            eat(tElse); stmtBlock();
        default:
            break;
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
            exprAssignOrCall(); eat(tSemiColon);
            break;
        case tSemiColon:
            eat(tSemiColon);
            break;
        default:
            vector<Token> tokens = {tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis};
            error(tokens);
            break;
    }
}

void whileStmt(){
    switch(tok){
        case tWhile:
            eat(tWhile); eat(tParLeft); expr(); eat(tParRight); stmt();
            break;
        default:
            vector<Token> tokens = {tWhile};
            error(tokens);
            break;
    }
}

void forStmt(){
    switch(tok){
        case tFor:
            eat(tFor); eat(tParLeft); exprAssignOrEmpty(); eat(tSemiColon); expr(); eat(tSemiColon); exprAssignOrEmpty(); eat(tParRight); stmt();
            break;
        default:
            vector<Token> tokens = {tFor};
            error(tokens);
            break;
    }
}

void returnStmt(){
    switch(tok){
        case tReturn:
            eat(tReturn); exprOrEmpty(); eat(tSemiColon);
            break;
        default:
            vector<Token> tokens = {tReturn};
            error(tokens);
            break;
    }
}

void breakStmt(){
    switch(tok){
        case tBreak:
            eat(tBreak); eat(tSemiColon);
            break;
        default:
            vector<Token> tokens = {tBreak};
            error(tokens);
            break;
    }
}

void printStmt(){
    switch(tok){
        case tPrint:
            eat(tPrint); eat(tParLeft); expr(); printOtherStmt();
            break;
        default:
            vector<Token> tokens = {tPrint};
            error(tokens);
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
            vector<Token> tokens = {tParRight, tComma};
            error(tokens);
            break;
    }
}

void classDec(){
    switch(tok){
        case tClass:
            eat(tClass); eat(tUserType); classDec1();
            break;
        default:
            vector<Token> tokens = {tClass};
            error(tokens);
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
            vector<Token> tokens = {tImplements, tBraceLeft};
            error(tokens);
            break;
    }
}

void implements(){
    switch(tok){
        case tComma:
            eat(tComma); eat(tUserType); implements();
            break;
        default:
            break;
    }
}

void field(){
    switch(tok){
        case tVoid:
            eat(tVoid); eat(tId); funcDec(); field();
            break;
        case tInt:
        case tDouble:
        case tBool:
        case tString:
        case tUserType: 
            var(); dec1(); field();
        default:
            break;
    }
}

void interDec(){
    switch(tok){
        case tInterface:
            eat(tInterface); eat(tUserType); eat(tBraceLeft); prototype(); eat(tBraceRight);
            break;
        default:
            vector<Token> tokens = {tInterface};
            error(tokens);
            break;
    }
}

void prototype(){
    switch(tok){
        case tVoid:
            eat(tVoid); eat(tId); eat(tParLeft); formals(); eat(tParRight); eat(tSemiColon);
            break;
        case tInt:
        case tDouble:
        case tBool:
        case tString:
        case tUserType:
            var(); eat(tParLeft); formals(); eat(tParRight); eat(tSemiColon);
            break;
        default:
            break;
    }
}

void exprAssign(){
    switch(tok){
        case tId:
        case tThis:
            lValue(); variableForAssignment(); eat(tAssignment); expr();
            break;
        default:
            vector<Token> tokens = {tId, tThis};
            error(tokens);
            break;
    }
}

void exprAssignOrCall(){
    switch(tok){
        case tId:
        case tThis:
            lValue(); variableForAssignment(); exprAssignOrCall1();
            break;
        default:
            vector<Token> tokens = {tId, tThis};
            error(tokens);
            break;
    }
}

void exprAssignOrCall1(){
    switch(tok){
        case tAssignment:
            eat(tAssignment); expr();
            break;
        case tParLeft:
            call();
            break;
        default:
            vector<Token> tokens = {tAssignment, tParLeft};
            error(tokens);
            break;
    }
}

void exprAssignOrEmpty(){
    switch(tok){
        case tId:
        case tThis:
            exprAssign();
            break;
        default:
            break;
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
        default:
            break;
    }
}

void relOp(){
    plusSubOp(); relOp1();
}

void relOp1(){
    switch(tok){
        case tLess:
            eat(tLess); plusSubOp(); relOp1();
            break;
        case tLessEqual:
            eat(tLessEqual); plusSubOp(); relOp1();
            break;
        case tGreater:
            eat(tGreater); plusSubOp(); relOp1();
            break;
        case tGreaterEqual:
            eat(tGreaterEqual); plusSubOp(); relOp1();
            break;
        case tEqual:
            eat(tEqual); plusSubOp(); relOp1();
            break;
        case tDiff:
            eat(tDiff); plusSubOp(); relOp1();
            break;
        default:
            break;
    }
}

void plusSubOp(){
    mulDivModOp(); plusSubOp1();
}

void plusSubOp1(){
    switch(tok){
        case tPlus:
            eat(tPlus); mulDivModOp(); plusSubOp1();
            break;
        case tMinus:
            eat(tMinus); mulDivModOp(); plusSubOp1();
            break;
        default:
            break;
    }
}

void mulDivModOp(){
    unaryOp(); mulDivModOp1(); 
}

void mulDivModOp1(){
    switch(tok){
        case tMulti:
            eat(tMulti); unaryOp(); mulDivModOp1();
            break;
        case tDiv:
            eat(tDiv); unaryOp(); mulDivModOp1();
            break;
        case tMod:
            eat(tMod); unaryOp(); mulDivModOp1();
            break;
        default:
            break;
    }
}

void unaryOp(){
    switch(tok){
        case tNot:
            eat(tNot); unaryOp();
            break;
        case tMinus:
            eat(tMinus); unaryOp(); 
            break;
        default:
            term();
            break;
    }
}

void term(){
    switch(tok){
        case tReadInteger:
            eat(tReadInteger); eat(tParLeft); eat(tParRight);
            break;
        case tReadLine:
            eat(tReadLine); eat(tParLeft); eat(tParRight);
            break;
        case tNew:
            eat(tNew); eat(tParLeft); eat(tId); eat(tParRight);
            break;
        case tNewArray:
            eat(tNewArray); eat(tParLeft); expr(); eat(tComma); type(); eat(tParRight);
            break;
        case tParLeft:
            eat(tParLeft); expr(); eat(tParRight);
            break;
        case tId:
        case tThis:
            lValue(); callOrVariable();
            break;
        case tIntConstant:
        case tDoubleConstant:
        case tTrue:
        case tFalse:
        case tStringConstant:
        case tNull:
            constant();
            break;
        default:
            vector<Token> tokens = {tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull};
            error(tokens);
            break;
    }
}

void callOrVariable(){
    switch(tok){
        case tParLeft:
            call();
            break;
        case tBracketLeft:
        case tDot:
            variable();
            break;
        default:
            break;
    }
}

void call(){
    switch(tok){
        case tParLeft:
            eat(tParLeft); actual(); eat(tParRight); callVariable();
            break;
        default:
            vector<Token> tokens = {tParLeft};
            error(tokens);
            break;
    }
}

void callVariable(){
    switch(tok){
        case tBracketLeft:
        case tDot:
            variableNotEmpty();
            break;
        default:
            break;
    }
}

void variableNotEmpty(){
    switch(tok){
        case tBracketLeft:
            eat(tBracketLeft); expr(); eat(tBracketRight); callAfterVariable();
            break;
        case tDot:
            eat(tDot); lValue(); callAfterVariable();
            break;
        default:
            vector<Token> tokens = {tBraceLeft, tDot};
            error(tokens);
            break;
    }
}

void callAfterVariable(){
    switch(tok){
        case tParLeft:
            call();
            break;
        case tBracketLeft:
        case tDot:
            variableNotEmpty();
            break;
        default:
            break;
    }
}

void variableForAssignment(){
    switch(tok){
        case tBracketLeft:
            eat(tBracketLeft); expr(); eat(tBracketRight); variableForAssignment();
            break;
        case tDot:
            eat(tDot); lValue(); variableForAssignment();
            break;
        default:
            break;
    }
}


void variable(){
    switch(tok){
        case tBracketLeft:
            eat(tBracketLeft); expr(); eat(tBracketRight); variable1();
            break;
        case tDot:
            eat(tDot); lValue(); variable1();
            break;
        default:
            break;
    }
}

void variable1(){
    switch(tok){
        case tBracketLeft:
            eat(tBracketLeft); expr(); eat(tBracketRight); variable1();
            break;
        case tDot:
            eat(tDot); lValue(); variable1();
            break;
        case tParLeft:
            call();
            break;
        default:
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
            vector<Token> tokens = {tId, tThis};
            error(tokens);
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

void exprSeq(){
    switch(tok){
        case tComma:
            eat(tComma); expr(); exprSeq();
            break;
        default:
            break;
    }
}

void actual(){
    switch(tok){
        case tNot:
        case tMinus:
        case tReadInteger:
        case tReadLine:
        case tNew:
        case tNewArray:
        case tParLeft:
        case tId:
        case tThis:
        case tIntConstant:
        case tDoubleConstant:
        case tTrue:
        case tFalse:
        case tStringConstant:
        case tNull:
            expr(); exprSeq();
            break;
        default:
            break;
    }
}

void constant(){
    switch(tok){
        case tIntConstant:
            eat(tIntConstant);
            break;
        case tDoubleConstant:
            eat(tDoubleConstant);
            break;
        case tTrue:
            eat(tTrue);
            break;
        case tFalse:
            eat(tFalse);
            break;
        case tStringConstant:
            eat(tStringConstant);
            break;
        case tNull:
            eat(tNull);
            break;
        default:
            vector<Token> tokens = {tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull};
            error(tokens);
            break;
    }
}

int main(int argc, char** args){
    if(argc > 1){
    	yyin = fopen(args[1], "r");
        advance();
        prog();
    }
    return 0;
}

void error(vector<Token> expected_tokens){

    cerr << "An error was found with lexema \"" << lexema << "\" at line " << row << ", column " << column << "." << endl;
    cerr << "Expected tokens: ";
    for(int i = 0; i < expected_tokens.size(); ++i){
        cerr << getTokenString(expected_tokens[i]);
        if(i + 2 == expected_tokens.size())
            cerr << " or ";
        else if(i + 1 < expected_tokens.size())
            cerr << ", ";
        else
            cerr << ".";
    }

    cerr << endl;

    exit(0);
}

void advance(){
    yylex();
}

void eat(Token t){
    if(t == tok){
        advance();
    }else{
        vector<Token> tokens = {t};
        error(tokens);
    }
}

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