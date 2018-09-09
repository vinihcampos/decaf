#ifndef _TABLE_H_
#define _TABLE_H_

#include "token.h"
#include <map>
#include <vector>
#include <utility>
#include <iostream>

enum NonTerminals {
    Prog = 500,
    Prog1, 
    Dec, 
    Dec1, 
    Var, 
    Type, 
    Type1, 
    FuncDec, 
    Formals, 
    Formals1, 
    Formals2, 
    StmtBlock, 
    StmtBlock1, 
    StatementList, 
    Stmt, 
    ConditionStmt, 
    OpTail, 
    OtherStmt, 
    WhileStmt, 
    ForStmt, 
    ReturnStmt, 
    BreakStmt, 
    PrintStmt, 
    PrintOtherStmt, 
    ClassDec, 
    ClassDec1, 
    ClassDec2, 
    Implements, 
    Field, 
    InterDec, 
    Prototype, 
    ExprAssign, 
    ExprAssignOrCall, 
    ExprAssignOrCall1, 
    ExprAssignOrEmpty, 
    Expr, 
    LogicOp, 
    RelOp, 
    RelOp1, 
    PlusSubOp, 
    PlusSubOp1, 
    MulDivModOp, 
    MulDivModOp1, 
    UnaryOp, 
    Term, 
    CallOrVariable, 
    Call, 
    CallVariable, 
    VariableNotEmpty, 
    CallAfterVariable, 
    Variable, 
    LValue, 
    ExprOrEmpty, 
    ExprSeq, 
    Actual, 
    Constant

};

std::map<std::pair<int, int>, std::vector<int>> table;


void init_table() {
    table[{Prog, tVoid}] = {Dec, Prog1};
    table[{Prog, tClass}] = {Dec, Prog1};
    table[{Prog, tInterface}] = {Dec, Prog1};
    table[{Prog, tInt}] = {Dec, Prog1};
    table[{Prog, tDouble}] = {Dec, Prog1};
    table[{Prog, tBool}] = {Dec, Prog1};
    table[{Prog, tString}] = {Dec, Prog1};
    table[{Prog, tUserType}] = {Dec, Prog1};

    table[{Prog1, tEOF}] = {};
    table[{Prog1, tVoid}] = {Prog};
    table[{Prog1, tClass}] = {Prog};
    table[{Prog1, tInterface}] = {Prog};
    table[{Prog1, tInt}] = {Prog};
    table[{Prog1, tDouble}] = {Prog};
    table[{Prog1, tBool}] = {Prog};
    table[{Prog1, tString}] = {Prog};
    table[{Prog1, tUserType}] = {Prog};

    table[{Dec, tClass}] = {ClassDec};
    table[{Dec, tInterface}] = {InterDec};
    table[{Dec, tInt}] = {Var, Dec1};
    table[{Dec, tDouble}] = {Var, Dec1};
    table[{Dec, tBool}] = {Var, Dec1};
    table[{Dec, tString}] = {Var, Dec1};
    table[{Dec, tUserType}] = {Var, Dec1};
    table[{Dec, tVoid}] = {tVoid, tId, FuncDec};

    table[{Dec1, tSemiColon}] = {tSemiColon};
    table[{Dec1, tParLeft}] = {FuncDec};

    table[{Var, tInt}] = {Type, tId};
    table[{Var, tDouble}] = {Type, tId};
    table[{Var, tBool}] = {Type, tId};
    table[{Var, tString}] = {Type, tId};
    table[{Var, tUserType}] = {Type, tId};

    table[{Type, tInt}] = {tInt, Type1};
    table[{Type, tDouble}] = {tDouble, Type1};
    table[{Type, tBool}] = {tBool, Type1};
    table[{Type, tString}] = {tString, Type1};
    table[{Type, tUserType}] = {tUserType, Type1};

    
    table[{Type1, tBracketLeft}] = {tBracketLeft, tBracketRight, Type1};
    table[{Type1, tId}] = {};
    table[{Type1, tParRight}] = {};

    table[{FuncDec, tParLeft}] = {tParLeft, Formals, tParRight, StmtBlock};

    //Formals : ε,tInt,tDouble,tBool,tString,tUserType
    table[{Formals, tInt}] = {Formals1};
    table[{Formals, tDouble}] = {Formals1};
    table[{Formals, tBool}] = {Formals1};
    table[{Formals, tString}] = {Formals1};
    table[{Formals, tUserType}] = {Formals1};
    table[{Formals, tParRight}] = {};
    
    //Formals1 : tInt,tDouble,tBool,tString,tUserType
    table[{Formals1, tInt}] = {Var, Formals2};
    table[{Formals1, tDouble}] = {Var, Formals2};
    table[{Formals1, tBool}] = {Var, Formals2};
    table[{Formals1, tString}] = {Var, Formals2};
    table[{Formals1, tUserType}] = {Var, Formals2};
    
    //Formals2 : ε,tComma
    table[{Formals2, tParRight}] = {};
    table[{Formals2, tComma}] = {tComma, Formals1};
    
    //StmtBlock : tBraceLeft
    table[{StmtBlock, tBraceLeft}] = {tBraceLeft, StmtBlock1, tBraceRight};

    //StmtBlock1 : ε,tInt,tDouble,tBool,tString,tUserType,tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    table[{StmtBlock1, tBraceRight}] = {};
    table[{StmtBlock1, tInt}] = {Var, tSemiColon, StmtBlock1};
    table[{StmtBlock1, tDouble}] = {Var, tSemiColon, StmtBlock1};
    table[{StmtBlock1, tBool}] = {Var, Formals2};
    table[{StmtBlock1, tString}] = {Var, Formals2};
    table[{StmtBlock1, tUserType}] = {Var, Formals2};
    table[{StmtBlock1, tIf}] = {StatementList};
    table[{StmtBlock1, tSemiColon}] = {StatementList};
    table[{StmtBlock1, tWhile}] = {StatementList};
    table[{StmtBlock1, tFor}] = {StatementList};
    table[{StmtBlock1, tBreak}] = {StatementList};
    table[{StmtBlock1, tReturn}] = {StatementList};
    table[{StmtBlock1, tPrint}] = {StatementList};
    table[{StmtBlock1, tBraceLeft}] = {StatementList};
    table[{StmtBlock1, tId}] = {StatementList};
    table[{StmtBlock1, tThis}] = {StatementList};    
    
    //StatementList : ε,tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    table[{StatementList, tBraceRight}] = {};
    table[{StatementList, tIf}] = {Stmt, StatementList};
    table[{StatementList, tSemiColon}] = {Stmt, StatementList};
    table[{StatementList, tWhile}] = {Stmt, StatementList};
    table[{StatementList, tFor}] = {Stmt, StatementList};
    table[{StatementList, tBreak}] = {Stmt, StatementList};
    table[{StatementList, tReturn}] = {Stmt, StatementList};
    table[{StatementList, tPrint}] = {Stmt, StatementList};
    table[{StatementList, tBraceLeft}] = {Stmt, StatementList};
    table[{StatementList, tId}] = {Stmt, StatementList};
    table[{StatementList, tThis}] = {Stmt, StatementList}; 

    //Stmt : tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    table[{Stmt, tIf}] = {ConditionStmt};
    table[{Stmt, tSemiColon}] = {OtherStmt};
    table[{Stmt, tWhile}] = {OtherStmt};
    table[{Stmt, tFor}] = {OtherStmt};
    table[{Stmt, tBreak}] = {OtherStmt};
    table[{Stmt, tReturn}] = {OtherStmt};
    table[{Stmt, tPrint}] = {OtherStmt};
    table[{Stmt, tBraceLeft}] = {OtherStmt};
    table[{Stmt, tId}] = {OtherStmt};
    table[{Stmt, tThis}] = {OtherStmt};

    //ConditionStmt : tIf
    table[{ConditionStmt, tIf}] = {tIf, tParLeft, Expr, tParRight, StmtBlock};

    //OpTail : tElse,ε
    //tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis,tBraceRight
    table[{OpTail, tBraceRight}] = {};
    table[{OpTail, tIf}] = {};
    table[{OpTail, tSemiColon}] = {};
    table[{OpTail, tWhile}] = {};
    table[{OpTail, tFor}] = {};
    table[{OpTail, tBreak}] = {};
    table[{OpTail, tReturn}] = {};
    table[{OpTail, tPrint}] = {};
    table[{OpTail, tBraceLeft}] = {};
    table[{OpTail, tId}] = {};
    table[{OpTail, tThis}] = {};
    table[{OpTail, tElse}] = {tElse, StmtBlock};
    //OtherStmt : tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    //WhileStmt : tWhile
    //ForStmt : tFor
    //ReturnStmt : tReturn
    //BreakStmt : tBreak
    //PrintStmt : tPrint
    //PrintOtherStmt : tParRight,tComma
    //ClassDec : tClass
    //ClassDec1 : tExtends,tImplements,tBraceLeft
    //ClassDec2 : tImplements,tBraceLeft
    //Implements : ε,tComma
    //Field : ε,tVoid,tInt,tDouble,tBool,tString,tUserType
    //InterDec : tInterface
    //Prototype : ε,tVoid,tInt,tDouble,tBool,tString,tUserType
    //ExprAssign : tId,tThis
    //ExprAssignOrCall : tId,tThis
    //ExprAssignOrCall1 : tAssignment,tParLeft
    //ExprAssignOrEmpty : ε,tId,tThis
    //Expr : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //LogicOp : ε,tOr,tAnd
    //RelOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //RelOp1 : ε,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff
    //PlusSubOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //PlusSubOp1 : ε,tPlus,tMinus
    //MulDivModOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //MulDivModOp1 : ε,tMulti,tDiv,tMod
    //UnaryOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //Term : tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //CallOrVariable : tParLeft,tBracketLeft,tDot,ε
    //Call : tParLeft
    //CallVariable : ε,tBracketLeft,tDot
    //VariableNotEmpty : tBracketLeft,tDot
    //CallAfterVariable : ε,tBracketLeft,tDot,tParLeft
    //Variable : ε,tBracketLeft,tDot
    //LValue : tId,tThis
    //ExprOrEmpty : ε,tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //ExprSeq : ε,tComma
    //Actual : ε,tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //Constant : tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
}

#endif