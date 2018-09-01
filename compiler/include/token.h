#ifndef _LEXICAL_
#define _LEXICAL_

enum Token{
	tVoid = 10,
	tInt,
	tDouble,  
	tBool,    
	tString,  
	tClass,
	tInterface,
	tNull,
	tThis,       
	tExtends,
	tImplements,
	tFor,
	tWhile,
	tIf,
	tElse,
	tReturn,
	tBreak,
	tNew,
	tNewArray,
	tPrint,
	tReadInteger,
	tReadLine,
	tId,
    tUserType,
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

char * getTokenString(int token){
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
		default:
			return "T_ERROR";
    }
}

#endif
