

#include <cstdio>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Structs' definitions
struct fun_partition{
int* arr;
int l;
int h;
int label;
};
struct fun_quickSortIterative{
int* arr;
int l;
int h;
int label;
};

// Stacks' definitions
stack<fun_partition> stack_fun_partition;
stack<fun_quickSortIterative> stack_fun_quickSortIterative;

// Returns' definitions
int return_fun_partition;

// Auxiliar variablesint pc = 0;
int label;
bool eval = false;
int readIntAux;
std::string readStringAux;

int main(){
int* vector;
int i;
vector = new int[10];
vector[0] = 42;
vector[1] = 34;
vector[2] = 9;
vector[3] = 56;
vector[4] = 90;
vector[5] = 17;
vector[6] = 49;
vector[7] = 27;
vector[8] = 94;
vector[9] = 11;
fun_quickSortIterative fun_quickSortIterative3;
fun_quickSortIterative3.arr = vector;
fun_quickSortIterative3.l = 0;
fun_quickSortIterative3.h = 9;
fun_quickSortIterative3.label = 4;
stack_fun_quickSortIterative.push(fun_quickSortIterative3);
label = 2;
goto labels;
continues4:
;
i = 0;label = 5;
goto labels;
for5:{
eval = i<10;
label = 6;
if(!eval) goto labels;
cout << vector[i]<< " "<< endl;
i = i+1;label = 5;
goto labels;
}
continue6:

return 0;
label_fun_partition:{
fun_partition fun_partition_;
fun_partition_ = stack_fun_partition.top();
int* arr;
arr = fun_partition_.arr;
int l;
l = fun_partition_.l;
int h;
h = fun_partition_.h;
int x;
int i;
int j;
int swap;
x = arr[h];
i = (l-1);
j = l;label = 7;
goto labels;
for7:{
eval = j<=h-1;
label = 8;
if(!eval) goto labels;
eval = arr[j]<=x;
label = 9;
if(eval) goto labels;
label = 10;
goto labels;
if9:{
i = i+1;
swap = arr[i];
arr[i] = arr[j];
arr[j] = swap;

label = 10;
goto labels;
}
continue10:

j = j+1;label = 7;
goto labels;
}
continue8:

swap = arr[i+1];
arr[i+1] = arr[h];
arr[h] = swap;
return_fun_partition = (i+1);
fun_partition auxReturn = stack_fun_partition.top();
stack_fun_partition.pop();
label = auxReturn.label;
goto labels;
}
label_fun_quickSortIterative:{
fun_quickSortIterative fun_quickSortIterative_;
fun_quickSortIterative_ = stack_fun_quickSortIterative.top();
int* arr;
arr = fun_quickSortIterative_.arr;
int l;
l = fun_quickSortIterative_.l;
int h;
h = fun_quickSortIterative_.h;
int* stack;
int top;
stack = new int[h-l+1];
top = -1;
top = top+1;
stack[top] = l;
top = top+1;
stack[top] = h;
label = 11;
goto labels;
while11:{
eval = top>=0;
label = 12;
if(!eval) goto labels;
int p;
h = stack[top];
top = top-1;
l = stack[top];
top = top-1;
fun_partition fun_partition13;
fun_partition13.arr = arr;
fun_partition13.l = l;
fun_partition13.h = h;
fun_partition13.label = 14;
stack_fun_partition.push(fun_partition13);
label = 1;
goto labels;
continues14:
p = return_fun_partition;
eval = p-1>l;
label = 15;
if(eval) goto labels;
label = 16;
goto labels;
if15:{
top = top+1;
stack[top] = l;
top = top+1;
stack[top] = p-1;

label = 16;
goto labels;
}
continue16:
eval = p+1<h;
label = 17;
if(eval) goto labels;
label = 18;
goto labels;
if17:{
top = top+1;
stack[top] = p+1;
top = top+1;
stack[top] = h;

label = 18;
goto labels;
}
continue18:

label = 11;
goto labels;
}
continue12:


fun_quickSortIterative auxReturn = stack_fun_quickSortIterative.top();
stack_fun_quickSortIterative.pop();
label = auxReturn.label;
goto labels;
}
labels:{
switch(label){
case(4):
goto continues4;
case(5):
goto for5;
case(6):
goto continue6;
case(1):
goto label_fun_partition;
case(7):
goto for7;
case(8):
goto continue8;
case(9):
goto if9;
case(10):
goto continue10;
case(2):
goto label_fun_quickSortIterative;
case(11):
goto while11;
case(12):
goto continue12;
case(14):
goto continues14;
case(15):
goto if15;
case(16):
goto continue16;
case(17):
goto if17;
case(18):
goto continue18;
default:
return 0;
}

}
}
