#include <cstdio>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Structs' definitions
struct Veiculo{
	string nome;
	string cor;
	int num_rodas;
};
struct Moto{
	double cilindradas;
};
struct method_toString{
	int label;
	Moto * attr;
};
struct Multiplicacao{
	Veiculo veiculo;
};
struct method_calculavel{
	int label;
	Multiplicacao * attr;
};
struct method_calcular{
	int label;
	Multiplicacao * attr;
};

// Stacks' definitions
stack<method_toString> stack_method_toString;
stack<method_calculavel> stack_method_calculavel;
stack<method_calcular> stack_method_calcular;

// Returns' definitions
string return_method_toString;
bool return_method_calculavel;
double return_method_calcular;

// Auxiliar variablesint pc = 0;
int label;
bool eval = false;
int readIntAux;
std::string readStringAux;

int main(){
	return 0;
	label_method_toString:{
		method_toString method_toString_;
		method_toString_ = stack_method_toString.top();
		return_method_toString = "";
		method_toString auxReturn = stack_method_toString.top();
		stack_method_toString.pop();
		label = auxReturn.label;
		goto labels;
	}
	label_method_calculavel:{
		method_calculavel method_calculavel_;
		method_calculavel_ = stack_method_calculavel.top();
		return_method_calculavel = 1;
		method_calculavel auxReturn = stack_method_calculavel.top();
		stack_method_calculavel.pop();
		label = auxReturn.label;
		goto labels;
	}
	label_method_calcular:{
		method_calcular method_calcular_;
		method_calcular_ = stack_method_calcular.top();
		return_method_calcular = 5*5;
		method_calcular auxReturn = stack_method_calcular.top();
		stack_method_calcular.pop();
		label = auxReturn.label;
		goto labels;
	}
	labels:{
		switch(label){
			case(0):
			goto label_method_toString;
			case(1):
			goto label_method_calculavel;
			case(2):
			goto label_method_calcular;
			default:
			return 0;
		}

	}
}
