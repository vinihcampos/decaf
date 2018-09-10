#ifndef _TABLE_H_
#define _TABLE_H_

#include "token.h"
#include <map>
#include <vector>
#include <utility>
#include <iostream>

enum NonTerminals {
    Prog = 501,
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
    VariableForAssignment,
    Variable,
    Variable1,
    LValue,
    ExprOrEmpty,
    ExprSeq,
    Actual,
    Constant
};

std::map<std::pair<int, int>, std::vector<int>> table;


void init_table() {
    //Prog : tVoid,tClass,tInterface,tInt,tDouble,tBool,tString,tUserType
    table[{Prog, tVoid}] = {Dec, Prog1};
    table[{Prog, tClass}] = {Dec, Prog1};
    table[{Prog, tInterface}] = {Dec, Prog1};
    table[{Prog, tInt}] = {Dec, Prog1};
    table[{Prog, tDouble}] = {Dec, Prog1};
    table[{Prog, tBool}] = {Dec, Prog1};
    table[{Prog, tString}] = {Dec, Prog1};
    table[{Prog, tUserType}] = {Dec, Prog1};

    //Prog1 : ε,tVoid,tClass,tInterface,tInt,tDouble,tBool,tString,tUserType
    //Prog1 : $
    table[{Prog1, tEOF}] = {};
    table[{Prog1, tVoid}] = {Prog};
    table[{Prog1, tClass}] = {Prog};
    table[{Prog1, tInterface}] = {Prog};
    table[{Prog1, tInt}] = {Prog};
    table[{Prog1, tDouble}] = {Prog};
    table[{Prog1, tBool}] = {Prog};
    table[{Prog1, tString}] = {Prog};
    table[{Prog1, tUserType}] = {Prog};

    //Dec : tVoid,tClass,tInterface,tInt,tDouble,tBool,tString,tUserType
    table[{Dec, tClass}] = {ClassDec};
    table[{Dec, tInterface}] = {InterDec};
    table[{Dec, tInt}] = {Var, Dec1};
    table[{Dec, tDouble}] = {Var, Dec1};
    table[{Dec, tBool}] = {Var, Dec1};
    table[{Dec, tString}] = {Var, Dec1};
    table[{Dec, tUserType}] = {Var, Dec1};
    table[{Dec, tVoid}] = {tVoid, tId, FuncDec};

    //Dec1 : tSemiColon,tParLeft
    table[{Dec1, tSemiColon}] = {tSemiColon};
    table[{Dec1, tParLeft}] = {FuncDec};

    //Var : tInt,tDouble,tBool,tString,tUserType
    table[{Var, tInt}] = {Type, tId};
    table[{Var, tDouble}] = {Type, tId};
    table[{Var, tBool}] = {Type, tId};
    table[{Var, tString}] = {Type, tId};
    table[{Var, tUserType}] = {Type, tId};

    //Type : tInt,tDouble,tBool,tString,tUserType
    table[{Type, tInt}] = {tInt, Type1};
    table[{Type, tDouble}] = {tDouble, Type1};
    table[{Type, tBool}] = {tBool, Type1};
    table[{Type, tString}] = {tString, Type1};
    table[{Type, tUserType}] = {tUserType, Type1};

    //Type1 : ε,tBracketLeft
    //Type1 : tId,tParRight
    table[{Type1, tId}] = {};
    table[{Type1, tBracketLeft}] = {tBracketLeft, tBracketRight, Type1};
    table[{Type1, tParRight}] = {};

    //FuncDec : tParLeft
    table[{FuncDec, tParLeft}] = {tParLeft, Formals, tParRight, StmtBlock};

    //Formals : ε,tInt,tDouble,tBool,tString,tUserType
    //Formals : tParRight
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
    //Formals2 : tParRight
    table[{Formals2, tParRight}] = {};
    table[{Formals2, tComma}] = {tComma, Formals1};
    
    //StmtBlock : tBraceLeft
    table[{StmtBlock, tBraceLeft}] = {tBraceLeft, StmtBlock1, tBraceRight};

    //StmtBlock1 : ε,tInt,tDouble,tBool,tString,tUserType,tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    //StmtBlock1 : tBraceRight
    table[{StmtBlock1, tId}] = {StatementList};
    table[{StmtBlock1, tThis}] = {StatementList};  
    table[{StmtBlock1, tInt}] = {Var, tSemiColon, StmtBlock1};
    table[{StmtBlock1, tDouble}] = {Var, tSemiColon, StmtBlock1};
    table[{StmtBlock1, tBool}] = {Var, Formals2};
    table[{StmtBlock1, tString}] = {Var, Formals2};
    table[{StmtBlock1, tUserType}] = {Var, Formals2};
    table[{StmtBlock1, tBraceLeft}] = {StatementList};
    table[{StmtBlock1, tBraceRight}] = {StatementList};
    table[{StmtBlock1, tIf}] = {StatementList};
    table[{StmtBlock1, tSemiColon}] = {StatementList};
    table[{StmtBlock1, tWhile}] = {StatementList};
    table[{StmtBlock1, tFor}] = {StatementList};
    table[{StmtBlock1, tBreak}] = {StatementList};
    table[{StmtBlock1, tReturn}] = {StatementList};
    table[{StmtBlock1, tPrint}] = {StatementList};
      
    
    //StatementList : ε,tIf,tSemiColon,tWhile,tFor,tBreak,tReturn,tPrint,tBraceLeft,tId,tThis
    //StatementList : tBraceRight
    table[{StatementList, tId}] = {Stmt, StatementList};
    table[{StatementList, tSemiColon}] = {Stmt, StatementList};
    table[{StatementList, tBraceLeft}] = {Stmt, StatementList};
    table[{StatementList, tBraceRight}] = {};
    table[{StatementList, tIf}] = {Stmt, StatementList};
    table[{StatementList, tWhile}] = {Stmt, StatementList};
    table[{StatementList, tFor}] = {Stmt, StatementList};
    table[{StatementList, tBreak}] = {Stmt, StatementList};
    table[{StatementList, tReturn}] = {Stmt, StatementList};
    table[{StatementList, tPrint}] = {Stmt, StatementList};
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
    table[{ConditionStmt, tIf}] = {tIf, tParLeft, Expr, tParRight, StmtBlock, OpTail};

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
    table[{OtherStmt, tId}] = {ExprAssignOrCall, tSemiColon};
    table[{OtherStmt, tSemiColon}] = {tSemiColon};
    table[{OtherStmt, tBraceLeft}] = {StmtBlock};
    table[{OtherStmt, tWhile}] = {WhileStmt};
    table[{OtherStmt, tFor}] = {ForStmt};
    table[{OtherStmt, tBreak}] = {BreakStmt};
    table[{OtherStmt, tReturn}] = {ReturnStmt};
    table[{OtherStmt, tPrint}] = {PrintStmt};
    table[{OtherStmt, tThis}] = {ExprAssignOrCall, tSemiColon};

    //WhileStmt : tWhile
    table[{WhileStmt, tWhile}] = {tWhile, tParLeft, Expr, tParRight, Stmt};
    
    //ForStmt : tFor
    table[{ForStmt, tFor}] = {tFor, tParLeft, ExprAssignOrEmpty, tSemiColon, Expr, tSemiColon, ExprAssignOrEmpty, tParRight, Stmt};
    
    //ReturnStmt : tReturn
    table[{ReturnStmt, tReturn}] = {tReturn, ExprOrEmpty, tSemiColon};

    //BreakStmt : tBreak
    table[{BreakStmt, tBreak}] = {tBreak, tSemiColon};
    
    //PrintStmt : tPrint
    table[{PrintStmt, tPrint}] = {tPrint, tParLeft, Expr, PrintOtherStmt};

    //PrintOtherStmt : tParRight,tComma
    table[{PrintOtherStmt, tParRight}] = {tParRight, tSemiColon};
    table[{PrintOtherStmt, tComma}] = {tComma, Expr, PrintOtherStmt};

    //ClassDec : tClass
    table[{ClassDec, tClass}] = {tClass, tUserType, ClassDec1};

    //ClassDec1 : tExtends,tImplements,tBraceLeft
    table[{ClassDec1, tExtends}] = {tExtends, tUserType, ClassDec2};
    table[{ClassDec1, tImplements}] = {ClassDec2};
    table[{ClassDec1, tBraceLeft}] = {ClassDec2};

    //ClassDec2 : tImplements,tBraceLeft
    table[{ClassDec2, tImplements}] = {tImplements, tUserType, Implements, tBraceLeft, Field, tBraceRight};
    table[{ClassDec2, tBraceLeft}] = {tBraceLeft, Field, tBraceRight};

    //Implements : ε,tComma
    //tBraceLeft
    table[{Implements, tBraceLeft}] = {};
    table[{Implements, tComma}] = {tComma, tUserType, Implements};

    //Field : ε,tVoid,tInt,tDouble,tBool,tString,tUserType
    //Field : tBraceRight
    table[{Field, tBraceRight}] = {};
    table[{Field, tVoid}] = {tVoid, tId, FuncDec, Field};
    table[{Field, tInt}] = {Var, Dec1, Field};
    table[{Field, tDouble}] = {Var, Dec1, Field};
    table[{Field, tBool}] = {Var, Dec1, Field};
    table[{Field, tString}] = {Var, Dec1, Field};
    table[{Field, tUserType}] = {Var, Dec1, Field};

    //InterDec : tInterface
    table[{InterDec, tInterface}] = {tInterface, tUserType, tBraceLeft, Prototype, tBraceRight};

    //Prototype : ε,tVoid,tInt,tDouble,tBool,tString,tUserType
    //Prototype : tBraceRight
    table[{Prototype, tBraceRight}] = {};
    table[{Prototype, tVoid}] = {tVoid, tId, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    table[{Prototype, tInt}] = {Var, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    table[{Prototype, tDouble}] = {Var, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    table[{Prototype, tBool}] = {Var, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    table[{Prototype, tString}] = {Var, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    table[{Prototype, tUserType}] = {Var, tParLeft, Formals, tParRight, tSemiColon, Prototype};
    
    //ExprAssign : tId,tThis
    table[{ExprAssign, tId}] = {LValue, VariableForAssignment, tAssignment, Expr};
    table[{ExprAssign, tThis}] = {LValue, VariableForAssignment, tAssignment, Expr};

    //ExprAssignOrCall : tId,tThis
    table[{ExprAssignOrCall, tId}] = {LValue, VariableForAssignment, ExprAssignOrCall1};
    table[{ExprAssignOrCall, tThis}] = {LValue, VariableForAssignment, ExprAssignOrCall1};

    //ExprAssignOrCall1 : tAssignment,tParLeft
    table[{ExprAssignOrCall1, tAssignment}] = {tAssignment, Expr};
    table[{ExprAssignOrCall1, tParLeft}] = {Call};

    //ExprAssignOrEmpty : ε,tId,tThis
    //tSemiColon,tParRight
    table[{ExprAssignOrEmpty, tSemiColon}] = {};
    table[{ExprAssignOrEmpty, tParRight}] = {};
    table[{ExprAssignOrEmpty, tId}] = {ExprAssign};
    table[{ExprAssignOrEmpty, tThis}] = {ExprAssign};

    //Expr : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{Expr, tId}] = {RelOp, LogicOp};
    table[{Expr, tParLeft}] = {RelOp, LogicOp};
    table[{Expr, tNot}] = {RelOp, LogicOp};
    table[{Expr, tMinus}] = {RelOp, LogicOp};
    table[{Expr, tReadInteger}] = {RelOp, LogicOp};
    table[{Expr, tReadLine}] = {RelOp, LogicOp};
    table[{Expr, tNew}] = {RelOp, LogicOp};
    table[{Expr, tNewArray}] = {RelOp, LogicOp};
    table[{Expr, tThis}] = {RelOp, LogicOp};
    table[{Expr, tIntConstant}] = {RelOp, LogicOp};
    table[{Expr, tDoubleConstant}] = {RelOp, LogicOp};
    table[{Expr, tTrue}] = {RelOp, LogicOp};
    table[{Expr, tFalse}] = {RelOp, LogicOp};
    table[{Expr, tStringConstant}] = {RelOp, LogicOp};
    table[{Expr, tNull}] = {RelOp, LogicOp};

    //LogicOp : ε,tOr,tAnd
    //LogicOp : tParRight,tSemiColon,tComma,tBracketRight
    table[{LogicOp, tSemiColon}] = {};
    table[{LogicOp, tBracketRight}] = {};
    table[{LogicOp, tParRight}] = {};//69
    table[{LogicOp, tComma}] = {};
    table[{LogicOp, tOr}] = {tOr, RelOp, LogicOp};//70
    table[{LogicOp, tAnd}] = {tAnd, RelOp, LogicOp};//71
    
    //RelOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{RelOp, tId}] = {PlusSubOp, RelOp1};
    table[{RelOp, tParLeft}] = {PlusSubOp, RelOp1};
    table[{RelOp, tMinus}] = {PlusSubOp, RelOp1};
    table[{RelOp, tNot}] = {PlusSubOp, RelOp1};
    table[{RelOp, tReadInteger}] = {PlusSubOp, RelOp1};
    table[{RelOp, tReadLine}] = {PlusSubOp, RelOp1};
    table[{RelOp, tNew}] = {PlusSubOp, RelOp1};
    table[{RelOp, tNewArray}] = {PlusSubOp, RelOp1};
    table[{RelOp, tThis}] = {PlusSubOp, RelOp1};
    table[{RelOp, tIntConstant}] = {PlusSubOp, RelOp1};
    table[{RelOp, tDoubleConstant}] = {PlusSubOp, RelOp1};
    table[{RelOp, tTrue}] = {PlusSubOp, RelOp1};
    table[{RelOp, tFalse}] = {PlusSubOp, RelOp1};
    table[{RelOp, tStringConstant}] = {PlusSubOp, RelOp1};
    table[{RelOp, tNull}] = {PlusSubOp, RelOp1};

    //RelOp1 : ε,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff
    //RelOp1 : tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{RelOp1, tSemiColon}] = {};
    table[{RelOp1, tParRight}] = {};//73
    table[{RelOp1, tComma}] = {};
    table[{RelOp1, tBracketRight}] = {};
    table[{RelOp1, tOr}] = {};
    table[{RelOp1, tAnd}] = {};
    table[{RelOp1, tLess}] = {tLess, PlusSubOp, RelOp1};//74
    table[{RelOp1, tLessEqual}] = {tLessEqual, PlusSubOp, RelOp1};
    table[{RelOp1, tGreater}] = {tGreater, PlusSubOp, RelOp1};
    table[{RelOp1, tGreaterEqual}] = {tGreaterEqual, PlusSubOp, RelOp1};
    table[{RelOp1, tEqual}] = {tEqual, PlusSubOp, RelOp1};
    table[{RelOp1, tDiff}] = {tDiff, PlusSubOp, RelOp1};//79

    //PlusSubOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{PlusSubOp, tId}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tParLeft}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tNot}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tMinus}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tReadInteger}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tReadLine}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tNew}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tNewArray}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tThis}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tIntConstant}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tDoubleConstant}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tTrue}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tFalse}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tStringConstant}] = {MulDivModOp, PlusSubOp1};
    table[{PlusSubOp, tNull}] = {MulDivModOp, PlusSubOp1};
    
    //PlusSubOp1 : ε,tPlus,tMinus
    //PlusSubOp1 : tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{PlusSubOp1, tSemiColon}] = {};
    table[{PlusSubOp1, tBracketRight}] = {};
    table[{PlusSubOp1, tParRight}] = {};//81
    table[{PlusSubOp1, tComma}] = {};
    table[{PlusSubOp1, tOr}] = {};
    table[{PlusSubOp1, tAnd}] = {};
    table[{PlusSubOp1, tLess}] = {};
    table[{PlusSubOp1, tLessEqual}] = {};
    table[{PlusSubOp1, tGreater}] = {};
    table[{PlusSubOp1, tGreaterEqual}] = {};
    table[{PlusSubOp1, tEqual}] = {};
    table[{PlusSubOp1, tDiff}] = {};
    table[{PlusSubOp1, tPlus}] = {tPlus, MulDivModOp, PlusSubOp1};//82
    table[{PlusSubOp1, tMinus}] = {tMinus, MulDivModOp, PlusSubOp1};//83

    //MulDivModOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{MulDivModOp, tId}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tParLeft}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tMinus}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tNot}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tReadInteger}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tReadLine}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tNew}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tNewArray}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tThis}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tIntConstant}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tDoubleConstant}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tTrue}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tFalse}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tStringConstant}] = {UnaryOp, MulDivModOp1};
    table[{MulDivModOp, tNull}] = {UnaryOp, MulDivModOp1};

    //MulDivModOp1 : ε,tMulti,tDiv,tMod
    //MulDivModOp1 : tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{MulDivModOp1, tSemiColon}] = {};//85
    table[{MulDivModOp1, tParRight}] = {};
    table[{MulDivModOp1, tBracketRight}] = {};
    table[{MulDivModOp1, tComma}] = {};
    table[{MulDivModOp1, tOr}] = {};
    table[{MulDivModOp1, tAnd}] = {};
    table[{MulDivModOp1, tLess}] = {};
    table[{MulDivModOp1, tLessEqual}] = {};
    table[{MulDivModOp1, tGreater}] = {};
    table[{MulDivModOp1, tGreaterEqual}] = {};
    table[{MulDivModOp1, tEqual}] = {};
    table[{MulDivModOp1, tDiff}] = {};
    table[{MulDivModOp1, tPlus}] = {};
    table[{MulDivModOp1, tMinus}] = {};
    table[{MulDivModOp1, tMulti}] = {tMulti, UnaryOp, MulDivModOp1};//86
    table[{MulDivModOp1, tDiv}] = {tDiv, UnaryOp, MulDivModOp1};//87
    table[{MulDivModOp1, tMod}] = {tMod, UnaryOp, MulDivModOp1};//88

    //UnaryOp : tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{UnaryOp, tId}] = {Term};//91
    table[{UnaryOp, tParLeft}] = {Term};
    table[{UnaryOp, tMinus}] = {tMinus, UnaryOp};//89
    table[{UnaryOp, tNot}] = {tNot, UnaryOp};//90
    table[{UnaryOp, tReadInteger}] = {Term};
    table[{UnaryOp, tReadLine}] = {Term};
    table[{UnaryOp, tNew}] = {Term};
    table[{UnaryOp, tNewArray}] = {Term};
    table[{UnaryOp, tThis}] = {Term};
    table[{UnaryOp, tIntConstant}] = {Term};
    table[{UnaryOp, tDoubleConstant}] = {Term};
    table[{UnaryOp, tTrue}] = {Term};
    table[{UnaryOp, tFalse}] = {Term};
    table[{UnaryOp, tStringConstant}] = {Term};
    table[{UnaryOp, tNull}] = {Term};

    //Term : tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{Term, tId}] = {LValue, CallOrVariable};//92
    table[{Term, tParLeft}] = {tParLeft, Expr, tParRight};//98
    table[{Term, tReadInteger}] = {tReadInteger, tParLeft, tParRight};//94
    table[{Term, tReadLine}] = {tReadLine, tParLeft, tParRight};//95
    table[{Term, tNew}] = {tNew, tParLeft, tId, tParRight};//96
    table[{Term, tNewArray}] = {tNewArray, tParLeft, Expr, tComma, Type, tParRight};//97
    table[{Term, tThis}] = {LValue, CallOrVariable};//92
    table[{Term, tIntConstant}] = {Constant};//93
    table[{Term, tDoubleConstant}] = {Constant};
    table[{Term, tTrue}] = {Constant};
    table[{Term, tFalse}] = {Constant};
    table[{Term, tStringConstant}] = {Constant};
    table[{Term, tNull}] = {Constant};

    //CallOrVariable : tParLeft,tBracketLeft,tDot,ε
    //CallOrVariable : tMulti,tDiv,tMod,tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{CallOrVariable, tSemiColon}] = {Variable};
    table[{CallOrVariable, tBracketLeft}] = {Variable};
    table[{CallOrVariable, tBracketRight}] = {Variable};
    table[{CallOrVariable, tParLeft}] = {Call};//99
    table[{CallOrVariable, tParRight}] = {Variable};
    table[{CallOrVariable, tComma}] = {Variable};
    table[{CallOrVariable, tOr}] = {Variable};
    table[{CallOrVariable, tAnd}] = {Variable};
    table[{CallOrVariable, tLess}] = {Variable};
    table[{CallOrVariable, tLessEqual}] = {Variable};
    table[{CallOrVariable, tGreater}] = {Variable};
    table[{CallOrVariable, tGreaterEqual}] = {Variable};
    table[{CallOrVariable, tEqual}] = {Variable};
    table[{CallOrVariable, tDiff}] = {Variable};
    table[{CallOrVariable, tPlus}] = {Variable};
    table[{CallOrVariable, tMinus}] = {Variable};
    table[{CallOrVariable, tMulti}] = {Variable};
    table[{CallOrVariable, tDiv}] = {Variable};
    table[{CallOrVariable, tMod}] = {Variable};
    table[{CallOrVariable, tDot}] = {Variable};

    //Call : tParLeft
    table[{Call, tParLeft}] = {tParLeft, Actual, tParRight, CallVariable};

    //CallVariable : ε,tBracketLeft,tDot
    //CallVariable : tSemiColon,tMulti,tDiv,tMod,tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tComma,tBracketRight
    table[{CallVariable, tSemiColon}] = {};//102
    table[{CallVariable, tBracketRight}] = {};
    table[{CallVariable, tParRight}] = {};
    table[{CallVariable, tComma}] = {};
    table[{CallVariable, tOr}] = {};
    table[{CallVariable, tAnd}] = {};
    table[{CallVariable, tLess}] = {};
    table[{CallVariable, tLessEqual}] = {};
    table[{CallVariable, tGreater}] = {};
    table[{CallVariable, tGreaterEqual}] = {};
    table[{CallVariable, tEqual}] = {};
    table[{CallVariable, tDiff}] = {};
    table[{CallVariable, tPlus}] = {};
    table[{CallVariable, tMinus}] = {};
    table[{CallVariable, tMulti}] = {};
    table[{CallVariable, tDiv}] = {};
    table[{CallVariable, tMod}] = {};
    table[{CallVariable, tBracketLeft}] = {VariableNotEmpty};//103
    table[{CallVariable, tDot}] = {VariableNotEmpty};

    //VariableNotEmpty : tBracketLeft,tDot
    table[{VariableNotEmpty, tBracketLeft}] = {tBracketLeft, Expr, tBracketRight, CallAfterVariable};
    table[{VariableNotEmpty, tDot}] = {tDot, LValue, CallAfterVariable};

    //CallAfterVariable : ε,tBracketLeft,tDot,tParLeft
    //CallAfterVariable : tSemiColon,tMulti,tDiv,tMod,tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tComma,tBracketRight
    table[{CallAfterVariable, tSemiColon}] = {};//106
    table[{CallAfterVariable, tParRight}] = {};
    table[{CallAfterVariable, tBracketRight}] = {};
    table[{CallAfterVariable, tComma}] = {};
    table[{CallAfterVariable, tOr}] = {};
    table[{CallAfterVariable, tAnd}] = {};
    table[{CallAfterVariable, tLess}] = {};
    table[{CallAfterVariable, tLessEqual}] = {};
    table[{CallAfterVariable, tGreater}] = {};
    table[{CallAfterVariable, tGreaterEqual}] = {};
    table[{CallAfterVariable, tEqual}] = {};
    table[{CallAfterVariable, tDiff}] = {};
    table[{CallAfterVariable, tPlus}] = {};
    table[{CallAfterVariable, tMinus}] = {};
    table[{CallAfterVariable, tMulti}] = {};
    table[{CallAfterVariable, tDiv}] = {};
    table[{CallAfterVariable, tMod}] = {};
    table[{CallAfterVariable, tBracketLeft}] = {VariableNotEmpty};//107
    table[{CallAfterVariable, tDot}] = {VariableNotEmpty};
    table[{CallAfterVariable, tParLeft}] = {Call};//108

    //VariableForAssignment : ε,tBracketLeft,tDot
    //VariableForAssignment : tAssignment,tParLeft
    table[{VariableForAssignment, tBracketLeft}] = {tBracketLeft, Expr, tBracketRight, VariableForAssignment};
    table[{VariableForAssignment, tParLeft}] = {};   
    table[{VariableForAssignment, tAssignment}] = {};
    table[{VariableForAssignment, tDot}] = {tDot, LValue, VariableForAssignment};

    //Variable : ε,tBracketLeft,tDot
    //Variable : tAssignment,tParLeft,tMulti,tDiv,tMod,tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{Variable, tSemiColon}] = {};//109
    table[{Variable, tBracketRight}] = {};
    table[{Variable, tParRight}] = {};
    table[{Variable, tComma}] = {};
    table[{Variable, tOr}] = {};
    table[{Variable, tAnd}] = {};
    table[{Variable, tLess}] = {};
    table[{Variable, tLessEqual}] = {};
    table[{Variable, tGreater}] = {};
    table[{Variable, tGreaterEqual}] = {};
    table[{Variable, tEqual}] = {};
    table[{Variable, tDiff}] = {};
    table[{Variable, tPlus}] = {};
    table[{Variable, tMinus}] = {};
    table[{Variable, tMulti}] = {};
    table[{Variable, tDiv}] = {};
    table[{Variable, tMod}] = {};
    table[{Variable, tBracketLeft}] = {tBracketLeft, Expr, tBracketRight, Variable1};
    table[{Variable, tDot}] = {tDot, LValue, Variable1};

    //Variable1 : ε,tBracketLeft,tDot,tParLeft
    //Variable1 : tMulti,tDiv,tMod,tPlus,tMinus,tLess,tLessEqual,tGreater,tGreaterEqual,tEqual,tDiff,tOr,tAnd,tParRight,tSemiColon,tComma,tBracketRight
    table[{Variable1, tSemiColon}] = {};//109
    table[{Variable1, tBracketRight}] = {};
    table[{Variable1, tParRight}] = {};
    table[{Variable1, tComma}] = {};
    table[{Variable1, tOr}] = {};
    table[{Variable1, tAnd}] = {};
    table[{Variable1, tLess}] = {};
    table[{Variable1, tLessEqual}] = {};
    table[{Variable1, tGreater}] = {};
    table[{Variable1, tGreaterEqual}] = {};
    table[{Variable1, tEqual}] = {};
    table[{Variable1, tDiff}] = {};
    table[{Variable1, tPlus}] = {};
    table[{Variable1, tMinus}] = {};
    table[{Variable1, tMulti}] = {};
    table[{Variable1, tDiv}] = {};
    table[{Variable1, tMod}] = {};
    table[{Variable1, tBracketLeft}] = {tBracketLeft, Expr, tBracketRight, Variable1};
    table[{Variable1, tDot}] = {tDot, LValue, Variable1};
    table[{Variable1, tParLeft}] = {Call};//118

    //LValue : tId,tThis
    table[{LValue, tId}] = {tId};
    table[{LValue, tThis}] = {tThis, tDot, tId};

    //ExprOrEmpty : ε,tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //ExprOrEmpty : tSemiColon
    table[{ExprOrEmpty, tId}] = {Expr};
    table[{ExprOrEmpty, tSemiColon}] = {};
    table[{ExprOrEmpty, tParLeft}] = {Expr};
    table[{ExprOrEmpty, tNot}] = {Expr};
    table[{ExprOrEmpty, tMinus}] = {Expr};
    table[{ExprOrEmpty, tReadInteger}] = {Expr};
    table[{ExprOrEmpty, tReadLine}] = {Expr};
    table[{ExprOrEmpty, tNew}] = {Expr};
    table[{ExprOrEmpty, tNewArray}] = {Expr};
    table[{ExprOrEmpty, tThis}] = {Expr};
    table[{ExprOrEmpty, tIntConstant}] = {Expr};
    table[{ExprOrEmpty, tDoubleConstant}] = {Expr};
    table[{ExprOrEmpty, tTrue}] = {Expr};
    table[{ExprOrEmpty, tFalse}] = {Expr};
    table[{ExprOrEmpty, tStringConstant}] = {Expr};
    table[{ExprOrEmpty, tNull}] = {Expr};

    //ExprSeq : ε,tComma
    //ExprSeq : tParRight
    table[{ExprSeq, tParRight}] = {};
    table[{ExprSeq, tComma}] = {tComma, Expr, ExprSeq};

    //Actual : ε,tNot,tMinus,tReadInteger,tReadLine,tNew,tNewArray,tParLeft,tId,tThis,tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    //Actual : tParRight

    table[{Actual, tId}] = {Expr, ExprSeq};
    table[{Actual, tParLeft}] = {Expr, ExprSeq};
    table[{Actual, tParRight}] = {};
    table[{Actual, tMinus}] = {Expr, ExprSeq};
    table[{Actual, tNot}] = {Expr, ExprSeq};
    table[{Actual, tReadInteger}] = {Expr, ExprSeq};
    table[{Actual, tReadLine}] = {Expr, ExprSeq};
    table[{Actual, tNew}] = {Expr, ExprSeq};
    table[{Actual, tNewArray}] = {Expr, ExprSeq};
    table[{Actual, tThis}] = {Expr, ExprSeq};
    table[{Actual, tIntConstant}] = {Expr, ExprSeq};
    table[{Actual, tDoubleConstant}] = {Expr, ExprSeq};
    table[{Actual, tTrue}] = {Expr, ExprSeq};
    table[{Actual, tFalse}] = {Expr, ExprSeq};
    table[{Actual, tStringConstant}] = {Expr, ExprSeq};
    table[{Actual, tNull}] = {Expr, ExprSeq};

    //Constant : tIntConstant,tDoubleConstant,tTrue,tFalse,tStringConstant,tNull
    table[{Constant, tIntConstant}] = {tIntConstant};
    table[{Constant, tDoubleConstant}] = {tDoubleConstant};
    table[{Constant, tTrue}] = {tTrue};
    table[{Constant, tFalse}] = {tFalse};
    table[{Constant, tStringConstant}] = {tStringConstant};
    table[{Constant, tNull}] = {tNull};
}

#endif