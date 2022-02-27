#include <iostream>
#include <sstream>
#include <cmath>
#include <conio.h>
#include <windows.h>
#include <vector>

using namespace std;


enum CMD_AND_COLORS
{
	c = 99,
	esc = 27,
	red = 12,
	green = 10,
	grey = 8,
	blue = 1, 
	yellow = 14, 
	white = 15, 
	black = 0, 
	darkYellow = 6,
	lightBlue = 3,
	darkGreen = 2, 
	darkRed = 4
};

//user's math funcs
double logBase(double arg, double base) {
   return log(arg) / log(base);
}

double sqrtBase(double arg, double base) {
	return pow(arg, 1 / base);
}

//service
void reverce(string &str) {
 	string str_2 = "";
	for(int i = str.size() - 1; i >= 0; i--) str_2 += str[i];	
	str = str_2;
}

void SetCur(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void SetColor(int text, int bg) { 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void SetColorText(int color1, string text, int color2) {
	SetColor(color1, black); 
	cout << text;
	SetColor(color2, black); 
}

//=============================main funcs
void calcSimpleExpr(string &expr) {
	
	expr = ' ' + expr + ' ';
	
	char emptyChar = ' ';
	string newExpr = "";
	char token = emptyChar;
	int tokenPos;
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == '^')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == '*' || expr[i] == '/')
		{
			token = expr[i];
			tokenPos = i;
			goto initInputData;
		} 
	}
	
	for(int i = 0; i < expr.size(); i++)
	{
		if(expr[i] == '+' || expr[i] == '-' && expr[i + 1] == emptyChar)
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
	
	id = tokenPos + 2;
	while(expr[id] != emptyChar)
		secondOperand += expr[id++];
	endConstr = id;
		
	id = tokenPos - 2;
	while(expr[id] != emptyChar)
		firstOperand += expr[id--];
	beginConstr = id + 1;
	
	reverce(firstOperand);
	
	//--------------------------calculation
	double res;
	double a = atof(firstOperand.c_str());
  	double b = atof(secondOperand.c_str());
  
	if(token == '+') res = a + b;
	else if(token == '-') res = a - b;
	else if(token == '*') res = a * b;
	else if(token == '^') res = pow(a, b);
	else try 
	{
		if(b == 0) throw "\nERROR: деление на ноль\n";
		res = a / b;
	}
	catch(const char* ex) 
	{
		cout << ex;
		res = a / b;
	}
	
	//-----------------------------------returning the result to main expression
	ostringstream ost;
  	ost << res;
  	string str_Res = ost.str();
	
	string firstPart = "";
  	string secondPart = "";
  	for(int i = 0; i < beginConstr; i++) firstPart += expr[i];
  	for(int i = endConstr; i < expr.size(); i++) secondPart += expr[i];
	expr = firstPart + str_Res + secondPart;
	
	for(int i = 1; i < expr.size() - 1; i++) 
		newExpr += expr[i];
	expr = newExpr;
	
	//cout << "S -> " << expr << endl;
	
	calcSimpleExpr(expr);
}

void openBrackets(string &expr) {
	
	expr = ' ' + expr + ' ';
	
	//-----------------------------------checking the availability of a open bracket
	int bracketFlag;
	char emptyChar = ' ';
	bool squareBracket = false;
	
	for(int j = expr.size() - 1; j >= 0; j--)
	{
		if(expr[j] == '|' && expr[j - 1] == emptyChar ||
		expr[j] == '|' && expr[j - 1] == '(' ||
		expr[j] == '|' && expr[j - 1] == '|') 
		{
			squareBracket = true;
			bracketFlag = j + 1; 
			goto isolationConstr;
		} 
		
		if(expr[j] == '(' && expr[j - 1] == emptyChar ||
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
		if(squareBracket) 
		{
			if(expr[i] != '|') insideBracketsConstr += expr[i];
			if(expr[i] == '|') 
			{
				endConstr = i; 
				break;
			}
		}
		else
		{
			if(expr[i] != ')') insideBracketsConstr += expr[i];
			if(expr[i] == ')') 
			{
				endConstr = i; 
				break;
			}
		}
	}
	
	//-----------------------------------calculation of the expr inside brackets
	calcSimpleExpr(insideBracketsConstr);
	if(squareBracket) 
	{
		double tmp;
		tmp = fabs(atof(insideBracketsConstr.c_str()));
		ostringstream ost;
  		ost << tmp;
  		insideBracketsConstr = ost.str();
	}
	
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
	
	//cout << "B -> " << expr << endl;
	
	openBrackets(expr);
}

//service
void strArgToDouble(string args, double &numArg) {
	
	for(auto elem : args) {
		if(elem == ' ') {
			openBrackets(args);
			calcSimpleExpr(args);
			break;
		}
	}
	numArg = atof(args.c_str()); //args -> double, calc	
}

//service
void strArgToDouble(string args, double &numArg1, double &numArg2) {
	
	int id = 0;
	
	repeatForSecondArg:
	string strArg = "";
	
	if(id == 0) 
	{
		while(args[id] != ',')
			strArg += args[id++];
		id++;
	}
	else
	{
		while(id != args.size()) 
			strArg += args[id++];
	}
	
	for(auto elem : strArg) {
		if(elem == ' ') {
			openBrackets(strArg);
			calcSimpleExpr(strArg);
			break;
		}
	}
	
	if(id != args.size()) 
	{
		numArg1 = atof(strArg.c_str()); 
		goto repeatForSecondArg;
	}	
	else numArg2 = atof(strArg.c_str()); 
}

void recognFunc(string &expr) {
	
	//-----------------------------------checking the availability of a function
	int funcFlag;
	string nameFunc = "";
	
	for(int j = expr.size() - 1; j >= 0; j--)
	{
		for(int i = 6; i >= 2; i--)
		{
			string tmp = "";
			
			for(int id = 0; id < i; id++) 
				tmp += expr[j - id];
			reverce(tmp);
			
			if(tmp == "arcsin" ||
			tmp == "arccos" ||
			tmp == "arctg" ||
			tmp == "arcctg" ||
			tmp == "sin" ||
			tmp == "cos" ||
			tmp == "tg" ||
			tmp == "ctg" ||
			tmp == "log" ||
			tmp == "ln" ||
			tmp == "lg" ||
			tmp == "sqrt") 
			{
				funcFlag = j - tmp.size() + 1; 
				nameFunc = tmp;
				goto isolationConstr;
			} 
		}
	}
	
	return;
	
	
	//-----------------------------------isolation of the funcConstruction
	isolationConstr:
		
	int sumOpenBracket = 0;
	string funcConstruction = "";
	int endFuncConstr;
	
	for(int i = funcFlag; i < expr.size(); i++)
	{	
		if(expr[i] == '(') sumOpenBracket++;
		if(expr[i] == ')') 
		{
			while(sumOpenBracket != 0)
			{
				funcConstruction += expr[i];
				if(expr[i] == ')') sumOpenBracket--;
				i++;
			} 
			endFuncConstr = i;
			break;
		}
		funcConstruction += expr[i];
	}
	
	
	//-----------------------------------calculation of the math function
	double res = 0;
	string args = "";
	const double PI = 3.141592653;
	const double DEGR_TO_RAD = PI / 180;
	const double RAD_TO_DEGR = 180 / PI;
	const double E = 2.7182818284;
	
	for(auto& elem : funcConstruction) 
	{
		if(elem != '(') elem = '$';
		else {elem = '$'; break;}
	} 
	funcConstruction[funcConstruction.size() - 1] = '$';
	
	for(auto elem : funcConstruction) 
		if(elem != '$') args += elem;
	
	
	//-----------------------------------recogning the function
	if(nameFunc == "log")
	{	
		double arg1, arg2;
		strArgToDouble(args, arg1, arg2);
  		res = logBase(arg1, arg2);
	}
	
	if(nameFunc == "ln")
	{	
		double arg;
		strArgToDouble(args, arg);
  		res = log(arg);
	}
	
	if(nameFunc == "lg")
	{	
		double arg;
		strArgToDouble(args, arg);
  		res = log10(arg);
	}
	
	if(nameFunc == "sin")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = sin(arg * DEGR_TO_RAD);
	}
	
	if(nameFunc == "cos")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = cos(arg * DEGR_TO_RAD);
	}
	
	if(nameFunc == "sqrt")
	{
		double arg1, arg2;
		
		for(auto elem : args)
			if(elem == ',') 
			{
				strArgToDouble(args, arg1, arg2);
				res = sqrtBase(arg1, arg2);
				goto gettingResInMainExpr;
			}
			
		strArgToDouble(args, arg1);
  		res = sqrt(arg1);
	}
	
	if(nameFunc == "tg")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = tan(arg * DEGR_TO_RAD);
	}
	
	if(nameFunc == "ctg")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = (1 / tan(arg * DEGR_TO_RAD));
	}
	
	if(nameFunc == "arcsin")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = asin(arg) * RAD_TO_DEGR;
	}
	
	if(nameFunc == "arccos")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = acos(arg) * RAD_TO_DEGR;
	}
	
	if(nameFunc == "arctg")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = atan(arg) * RAD_TO_DEGR;
	}
	
	if(nameFunc == "arcctg")
	{
		double arg;
		strArgToDouble(args, arg);
  		res = (PI / 2 - atan(arg)) * RAD_TO_DEGR;
	}
	
	//-----------------------------------returning the result to main expression
	gettingResInMainExpr:
	
  	ostringstream ost;
  	ost << res;
  	string str_Res = ost.str();
  	
  	string firstPart = "";
  	string secondPart = "";
  	for(int i = 0; i < funcFlag; i++) firstPart += expr[i];
  	for(int i = endFuncConstr; i < expr.size(); i++) secondPart += expr[i];
	expr = firstPart + str_Res + secondPart;
	
	//cout << "F -> " << expr << endl;
	
	recognFunc(expr);
}


//interface
string inputAndInterpretation() {
	
	//-----------------------input
	string expr = "";
	getline(cin, expr);
	
	//-----------------------exceptions
	try 
	{
		vector<string> exceptions;
		int quanOpenBr = 0;
		int quanCloseBr = 0;
		int quanSquareOpenBr = 0;
		int quanSquareCloseBr = 0;
		int quanBrMod = 0;
		
		for(auto elem : expr)
		{
			if(elem == '(') quanOpenBr++;
			if(elem == ')') quanCloseBr++;
			if(elem == '[') quanSquareOpenBr++;
			if(elem == ']') quanSquareCloseBr++;
			if(elem == '|') quanBrMod++;
		}
		
		if(quanOpenBr != quanCloseBr) exceptions.push_back("\nERROR: несовпадение круглых открывающих и закрывающих скобок");
		if(quanSquareOpenBr != quanSquareCloseBr) exceptions.push_back("\nERROR: несовпадение квадратных открывающих и закрывающих скобок");
		if(quanBrMod % 2 != 0) exceptions.push_back("\nERROR: несовпадение открывающих и закрывающих скобок модуля");
		if(!exceptions.empty()) throw exceptions;
	}
	catch(vector<string> ex) 
	{
		for(auto elem : ex) 
			cout << elem;
		return "";
	}
		
	//-----------------------interpretation
	string newExpr = "";
	const char emptyChar = ' ';
	 
	for(auto elem : expr)
		if(elem != emptyChar) newExpr += elem;
	expr = newExpr;
	
	int start = 0;
	repeatRecognToken:
	int tokenPos = -1;
	
	for(int i = start; i < expr.size(); i++)
	{
		if(expr[i] == '^' ||
		expr[i] == '*' ||
		expr[i] == '/' ||
		expr[i] == '+' ||
		expr[i] == '-' && i != 0 && expr[i - 1] != emptyChar && expr[i - 1] != '(' && expr[i - 1] != '[')
		{
			tokenPos = i;
			start = i + 3;
			break;
		}
	}
	
	if(tokenPos == -1) return expr; 
	
	string firstPart = "";
  	string secondPart = "";
  	for(int i = 0; i < tokenPos; i++) firstPart += expr[i];
  	for(int i = tokenPos + 1; i < expr.size(); i++) secondPart += expr[i];
	expr = firstPart + " " + expr[tokenPos] + " " + secondPart;
	
	//cout << "E -> |" << expr << "|" << endl;
	
	goto repeatRecognToken; 
}

int main() {
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int idResult = 1;
	
	cout << "\nДоступные функции\n-----------------\n";
	cout << "ln(x) - возвращает натуральный логарифм числа х\n";
	cout << "lg(x) - возвращает десятичный логарифм числа х\n";
	cout << "log(x, y) - возвращает логарифм числа Х с основанием У\n";
	cout << "tg(x) - возвращает тангенс х, представленного в градусах\n";
	cout << "ctg(x) - возвращает котангенс х, представленного в градусах\n";
	cout << "sin(x) - возвращает синус х, представленного в градусах\n";
	cout << "cos(x) - возвращает косинус х, представленного в градусах\n";
	cout << "sqrt(x) - возвращает квадратный корень из числа х\n";
	cout << "sqrt(x, n) - возвращает корень из числа х с показателем n\n";
	cout << "arcsin(x) - возвращает арксинус числа х\n";
	cout << "arccos(x) - возвращает арккосинус числа х\n";
	cout << "arctg(x) - возвращает арктангенс числа х\n";
	cout << "arcctg(x) - возвращает арккотангенс числа х\n";
	cout << "x ^ y - возводит х в степень у\n";
	cout << "|x| - возвращает модуль числа х\n";
	SetColorText(green, "\nДля выхода нажмите CTRL+C,\nдля вычисления - ENTER\n", white);
	
	repeat:
	cout << "\nВведите выражение:\n\n";
	
	string expr = inputAndInterpretation();
	recognFunc(expr);
	openBrackets(expr); 
	calcSimpleExpr(expr);
	
	SetColor(red, black);
	printf("\n%d. RESULT: ", idResult);
	idResult++;
	SetColor(white, black);
	cout << expr << "\n-----------------\n";
	goto repeat;
	
	return 0;
}
