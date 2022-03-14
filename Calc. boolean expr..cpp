
/*
	Name: bool calc
	Copyright: 
	Author: Louis
	Date: 14.03.22 19:41
	Description: calculator of boolean expression 
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <windows.h>
#include <conio.h>

using namespace std;

//------------------------------prototypes
void inputAndInterpretation(string &expr);
void calcSimpleExpr(string &expr);
void reverce(string &str);
void openBrackets(string &expr);
char* DecBin(int chislo, int size);
void setColor(int text, int bg);
void creatingBoolTable(string main_expr);


int main() {	

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	printf("Доступные символы\n");
	printf("-----------------\n");
	printf("! - отрицание\n");
	printf("& - конъюнкция\n");
	printf("v, V - дизъюнкция\n");
	printf("x, X - исключающее ИЛИ\n");
	printf("-> - импликация\n");
	printf("<=> - соответствие\n");
	setColor(10, 0);
	printf("\nДля выхода нажмите CTRL+C,\nдля вычисления - ENTER\n");
	setColor(12, 0);
	printf("\nИспользуйте в переменных латинские буквы, кроме x, X, v, V!\n");
	setColor(15, 0);
	
	repeat:
	cout << "\nВведите логическое выражение:\n";
	string main_expr;
	getline(cin, main_expr); 
	creatingBoolTable(main_expr);
	goto repeat;
	
	return 0;
}


//------------------------------service funcs
void setColor(int text, int bg) { 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void reverce(string &str) {
 	string str_2 = "";
	for(int i = str.size() - 1; i >= 0; i--) str_2 += str[i];	
	str = str_2;
}

char* DecBin(int chislo, int size) {
    char* bin = new char[size];
	for(int i = size - 1; i >= 0; --i)
        bin[i] = ((chislo>>i)&1) + 48;
    return bin;
}

//------------------------------funcs
void creatingBoolTable(string main_expr) {
	
	vector<string> exprs_for_calc;
	vector<string> vars_vect;
	map<string, char> vars;
	string expr = main_expr;
	cout << endl;
	
	for(auto &elem : expr) 
	{
		if(elem == 'v' || elem == 'V' ||
		elem == 'x' || elem == 'X' ||
		elem == '&' || elem == '-' || 
		elem == '=' || elem == '>' ||
		elem == '(' || elem == ')' ||
		elem == '<' || elem == '!' || 
		elem == '0' || elem == '1' || 
		elem == ' ') 
			elem = '#'; 
	}
	
	if(expr[0] != '#') expr = '#' + expr;
	if(expr[expr.size() - 1] != '#') expr += '#';
	
	string var_name = "";
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] != '#') 
			var_name += expr[i];
			
		else if(expr[i] == '#' && expr[i - 1] != '#') 
		{
			vars[var_name] = 0;
			var_name = "";
		}
	}
	
	vars.erase(vars.find(""));  

	for(auto elem : vars)
	{
		vars_vect.push_back(elem.first);
		cout << " " << elem.first;
	}
	
	cout << " | F\n";
	for(auto elem : vars)
		cout << "--";
	cout << "-----\n";
	
	//-----------------------init bool table
	int m = vars.size(), n = pow(2, m);
    int size(sizeof(m) * 8);
    string varsTable_Char[n];
    
    for(int num = 0; num < n; num++)
    {
    	char *bin = DecBin(num, size); 
    	string str = "";
    	for(int i = m - 1; i >= 0; i--)
			str += bin[i];
		varsTable_Char[num] = str;
	}

	for(int i = 0; i < n; i++)
	{
		string local_expr = main_expr;
		
		for(int j = 0; j < m; j++)	
		{
			vars[vars_vect[j]] = varsTable_Char[i][j];
			cout << " " << vars[vars_vect[j]];
		}
		
		for(auto elem : vars_vect)
		{
			for(int var_start = 0; var_start <= local_expr.size() - elem.size(); var_start++)
			{
				string var_name = "";
				for(int idVarSimbol = var_start; idVarSimbol < var_start + elem.size(); idVarSimbol++)
					var_name += local_expr[idVarSimbol];
				if(var_name == elem)
					local_expr[var_start] = vars[elem];
			}
			
		}
		
		exprs_for_calc.push_back(local_expr);
		
		//calculation
		inputAndInterpretation(local_expr);
		openBrackets(local_expr);
		calcSimpleExpr(local_expr);
		
		cout << " | " << local_expr;
		cout << endl;
	}
}

void inputAndInterpretation(string &expr) {
	//input
	//cout << "Input the bool expr:\n";
	//getline(cin, expr);
	
	//interpretation
	string newExpr = "";
	const char emptyChar = ' ';
	
	for(auto elem : expr)
		if(elem != emptyChar) newExpr += elem;
	expr = newExpr;
	
	//-------------------------
	int start = 0;
	repeatRecognToken:
	int tokenPos = -1;
	
	for(int i = start; i < expr.size(); i++)
	{
		if(expr[i] == 'V' || expr[i] == 'X' ||
		expr[i] == 'v' || expr[i] == '-' ||
		expr[i] == 'x' || expr[i] == '&' ||
		expr[i] == '<' || expr[i] == '>')
		{
			tokenPos = i;
			start = i + 2;
			break;
		}
	}
	
	if(tokenPos == -1) return; 
	
	string firstPart = "";
  	string secondPart = "";
  	for(int i = 0; i < tokenPos; i++) 
	  	firstPart += expr[i];
  	for(int i = tokenPos + 1; i < expr.size(); i++) 
	  	secondPart += expr[i];
	  	
	if(expr[tokenPos] == '>')
		expr = firstPart + expr[tokenPos] + " " + secondPart;
	else if(expr[tokenPos] == '<' || expr[tokenPos] == '-')
		expr = firstPart + " " + expr[tokenPos] + secondPart;
	else
		expr = firstPart + " " + expr[tokenPos] + " " + secondPart;
	
	//cout << "E: |" << expr << "|" << endl;
	goto repeatRecognToken; 
}

void calcSimpleExpr(string &expr) {
	
	expr = ' ' + expr + ' ';
	
	char emptyChar = ' ';
	string newExpr = "";
	char token = emptyChar;
	int tokenPos;
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == '!')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == '&')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == 'v' || expr[i] == 'x' || 
			expr[i] == 'V' || expr[i] == 'X')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++) //->
	{
		if(expr[i] == '-')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++) //<=>
	{
		if(expr[i] == '<')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(auto& elem : expr) 
		if(elem != emptyChar) newExpr += elem;
	expr = newExpr;
	
	return;
	
	//--------------------------initializing input data
	initInputData:
		
	int beginConstr, endConstr, id;
	string firstOperand = "";
	string secondOperand = "";
	
	if(expr[tokenPos] == '<')
	{
		id = tokenPos - 2;
		while(expr[id] != emptyChar)
			firstOperand += expr[id--];
		beginConstr = id + 1;
		
		id = tokenPos + 4;
		while(expr[id] != emptyChar)
			secondOperand += expr[id++];
		endConstr = id;
	}
	else if(expr[tokenPos] == '-')
	{
		id = tokenPos - 2;
		while(expr[id] != emptyChar)
			firstOperand += expr[id--];
		beginConstr = id + 1;
		
		id = tokenPos + 3;
		while(expr[id] != emptyChar)
			secondOperand += expr[id++];
		endConstr = id;
	}
	else if(expr[tokenPos] == '!')
	{
		id = tokenPos - 1;
		while(expr[id] != emptyChar)
			firstOperand += expr[id--];
		beginConstr = id + 1;
		
		id = tokenPos + 1;
		while(expr[id] != emptyChar)
			secondOperand += expr[id++];
		endConstr = id;
	}
	else 
	{
		id = tokenPos - 2;
		while(expr[id] != emptyChar)
			firstOperand += expr[id--];
		beginConstr = id + 1;
		
		id = tokenPos + 2;
		while(expr[id] != emptyChar)
			secondOperand += expr[id++];
		endConstr = id;
	}
	
	reverce(firstOperand);
	
	//--------------------------calculation
	bool res, a, b;
  	if(firstOperand == "0") a = 0; else a = 1;
  	if(secondOperand == "0") b = 0; else b = 1;
  
	if(token == '!') res = !b;
	else if(token == '&') res = (a && b);
	else if(token == 'V' || token == 'v') res = (a || b);
	else if(token == 'X' || token == 'x') res = (a != b);
	else if(token == '-') res = (!a || b);
	else if(token == '<') res = (a == b);
	
	//-----------------------------------returning the result to main expression
  	string str_Res;
  	string firstPart = "";
  	string secondPart = "";
  	
	if(res == false) str_Res = "0"; else str_Res = "1";
	
  	for(int i = 0; i < beginConstr; i++) 
	  	firstPart += expr[i];
  	for(int i = endConstr; i < expr.size(); i++) 
	  	secondPart += expr[i];
	expr = firstPart + str_Res + secondPart;
	
	for(int i = 1; i < expr.size() - 1; i++) 
		newExpr += expr[i];
	expr = newExpr;

	//cout << "S: " << expr << endl;
	
	calcSimpleExpr(expr);
}

void openBrackets(string &expr) {
	
	expr = ' ' + expr + ' ';
	
	//-----------------------------------checking the availability of a open bracket
	int bracketFlag;
	char emptyChar = ' ';
	
	for(int j = expr.size() - 1; j >= 0; j--)
	{	
		if(expr[j] == '(' && expr[j - 1] == emptyChar ||
		expr[j] == '(' && expr[j - 1] == '!' ||
		expr[j] == '(' && expr[j - 1] == '(') 
		{
			bracketFlag = j + 1; 
			goto isolationConstr;
		} 
	}
	
	return;
	
	//-----------------------------------isolation of the funcConstruction
	isolationConstr:
	string insideBracketsConstr = "";
	int endConstr;
	
	for(int i = bracketFlag; i < expr.size(); i++)
	{	
		if(expr[i] != ')') 
			insideBracketsConstr += expr[i];
		if(expr[i] == ')') 
		{
			endConstr = i; 
			break;
		}
	}
	
	//-----------------------------------calculation of the expr inside brackets
	calcSimpleExpr(insideBracketsConstr);
	
	//-----------------------------------returning the result to main expression
  	string firstPart = "";
  	string secondPart = "";
  	for(int i = 0; i < bracketFlag - 1; i++) firstPart += expr[i];
  	for(int i = endConstr + 1; i < expr.size(); i++) secondPart += expr[i];
	expr = firstPart + insideBracketsConstr + secondPart;
	
	string newExpr = "";
	for(int i = 1; i < expr.size() - 1; i++) 
		newExpr += expr[i];
	expr = newExpr;
	
	//cout << "B: " << expr << endl;
	
	openBrackets(expr);
}
