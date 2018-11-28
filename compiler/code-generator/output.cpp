#include <cstdio>
#include <iostream>
#include <stack>
#include <string>

using namespace std;


// Struts' definitions
struct funsoma{
};
struct funmulti{
int a;
int b;
};

// Stacks' definitions
stack<funsoma> stacksoma;
stack<funmulti> stackmulti;
int pc = 0;
int label;
bool eval = false;
int readIntAux;
std::string readStringAux;

int main(){
eval = 0;
label = 0;
if(eval) goto labels;
label = 1;
goto labels;
if0:{
"oi";

label = 1;
goto labels;
}
continue1:
;
return 0;
labels: 
switch(label){
case(0):
goto if0;
case(1):
goto continue1;
default:
return 0;
}

}