#ifndef _LEXICAL_
#define _LEXICAL_

enum Token{
	tVoid = 1,   	// base type
	tInt,        	// base type
	tDouble,     	// base type
	tBool,       	// base type
	tString,     	// base type
	tClass,      	// class
	tInterface,  	// interface
	tNull,       	// null
	tThis,       
	tExtends,    	// class
	tImplements, 	// interface
	tFor,	     	// loop
	tWhile,      	// loop
	tIf,         	// conditional
	tElse,       	// conditional
	tReturn,     	// subprogram return
	tBreak,      	// break statement
	tNew,		 	// expression
	tNewArray,   	// expression
	tPrint,		 	// print statement
	tReadInteger,	// read int
	tReadLine,   	// read string
	tId,		 	// Identifier (variable, class, interface or subprogram)
	tPlus,
	tMinus,
	tMulti,
	tDiv,
	tMod,
	tLess,
	tLessEqual,
	tGreater,
	tGreaterEqual,
	tEqual,
	tDiff,
	tAssignment,
	tAnd,
	tOr,
	tNot,
	tSemiColon,
	tComma,
	tDot,
	tBracketLeft,
	tBracketRight,
	tParLeft,
	tParRight,	
	tBraceLeft,
	tBraceRight,
	tIntConstant,
	tDoubleConstant,
	tTrue,
	tFalse,
	tStringConstant,
};

#endif
