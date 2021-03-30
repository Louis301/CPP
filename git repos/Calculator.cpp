#include <iostream>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <sstream>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
using namespace std;

void SetColor(int text, int bg) 
{ 
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

string reverce(string str) //реверс строки
{
	int i;
	string str_2;
	for(i = str.size() - 1; i >= 0; i--) {
		str_2 += str[i];
	}	
	return str_2;
}

double pr_vir(string p_v) //обработка простого выражения
{	
	int i, znak, z_i; double a = 0, b = 0;
	string a_str = "", b_str = "";
	
	for(i = 0; i <= p_v.size() - 1; i++) {
		if(p_v[i] == '+') {znak = 1; z_i = i; break;}
		if(p_v[i] == '-' && i != 0) {znak = 2; z_i = i; break;}
		if(p_v[i] == '*') {znak = 3; z_i = i; break;}
		if(p_v[i] == '/') {znak = 4; z_i = i; break;}
	}
	
	for(i = 0; i <= p_v.size() - 1; i++) {
		if(i >= 0 && i < z_i) a_str += p_v[i];
		if(i > z_i && i <= p_v.size() - 1) b_str += p_v[i];
	}
 
  a = atof(a_str.c_str());
  b = atof(b_str.c_str());
  
	if(znak == 1) return a + b;
	if(znak == 2) return a - b;
	if(znak == 3) return a * b;
	if(znak == 4) return a / b;
}

double sl_vir(string s) //обработка сложного выражения
{
	int i, j, a_i, b_i, n = 0, m, k = 0, r = 0;
	double num_p_v;
	string a_str = "", b_str = "", p_v = "", s_num;
	char empty = ' ';
	
	for(i = 0; i < s.size(); i++) {
		if(s[i] == '/' || s[i] == '*') n++;
	}
	for(i = 0; i < s.size(); i++) {
		if(s[i] == '-'  && s[i + 1] == empty && s[i - 1] == empty 
		|| s[i] == '+'  && s[i + 1] == empty && s[i - 1] == empty) k++;
	}
	
    for(m = 0; m < n; m++) {
    	for(i = 0; i < s.size(); i++) {
    		j = i;
    		if(s[i] == '*'  && s[i + 1] == empty && s[i - 1] == empty
			|| s[i] == '/'  && s[i + 1] == empty && s[i - 1] == empty) {

		    	j -= 2;
		    	while(s[j] != empty) {
		    		j--;
				} 

				a_i = j; j = 0;
				while(j >= 0 && j <= a_i) {
					a_str += s[j];
					j++; 
				}
				  
				j = a_i;  
				while(r != 3) {
					j++;
		    		if(s[j] == empty) {
		    			r++;
		    			if(r == 3) {
		    				r = 0; break;
						}
					}
		    		p_v += s[j];
				} 

				b_i = j; 
				while(j >= b_i && j < s.size()) {
					b_str += s[j];
					j++; 
				}
				
				num_p_v = pr_vir(p_v);
				ostringstream ost;
                ost << num_p_v;
                s_num = ost.str();
                
                s = a_str + s_num + b_str;
                a_str = ""; b_str = ""; p_v = ""; 
                break;
			}
		}
	}
    
    for(m = 0; m < k; m++) {
    	for(i = 0; i < s.size(); i++) {
    		j = i;
    		if(s[i] == '+'  && s[i + 1] == empty && s[i - 1] == empty
			|| s[i] == '-'  && s[i + 1] == empty && s[i - 1] == empty) {
                j = 0;
				while(r != 3) {
					j++;
		    		if(s[j] == empty) {
		    			r++;
		    			if(r == 3) {
		    				r = 0; break;
						}
					}
		    		p_v += s[j];
				} 

				b_i = j; 
				while(j >= b_i && j < s.size()) {
					b_str += s[j];
					j++; 
				}
				
				num_p_v = pr_vir(p_v);
				ostringstream ost;
                ost << num_p_v;
                s_num = ost.str();
                
                s = " " + s_num + b_str;
                b_str = ""; p_v = ""; 
                break;
		}
	}
}
return atof(s.c_str());
}

string perevod(string s) { //перевод в машинную строку
	int i, j, znak_s, znak_p = -1;
    string a_str = "", b_str = "", s_2;
    char s_zn, empty = ' ';
    
 	for(i = 0; i < s.size(); i++) {
    	j = i;
    	if(s[i] == '-' || s[i] == '+') {    				
    		    if(s[i - 1] != '-' && s[i - 1] != '+' && s[i - 1] != empty 
				&& s[i - 1] != '*' && s[i - 1] != '/' && s[i - 1] != ')') {
    		        znak_s = j; s_zn = s[znak_s]; 
    		        if(znak_s != znak_p + 1) {
			        j--;
    		        while(j < znak_s && j >= 0) {a_str += s[j]; j--;}
    		        j = znak_s + 1;
    		        while(j > znak_s && j < s.size()) {b_str += s[j]; j++;}
    		        s_2 = reverce(a_str) + " " + s_zn + " " + b_str;
    		        a_str = ""; b_str = ""; s = s_2; znak_p = znak_s; 
    		        }
    		        if(znak_s == znak_p + 1) continue;    		    
    	        }    	    
		}
	}
    
 	for(i = 0; i < s.size(); i++) {
    	j = i;
    	if(s[i] == '*' || s[i] == '/') {
    		znak_s = j; s_zn = s[znak_s]; 
    		if(znak_s != znak_p + 1) {
			    j--;
    		    while(j < znak_s && j >= 0) {a_str += s[j]; j--;}
    		    j = znak_s + 1;
    		    while(j > znak_s && j < s.size()) {b_str += s[j]; j++;}
    		    s_2 = reverce(a_str) + " " + s_zn + " " + b_str;
    		    a_str = ""; b_str = ""; s = s_2; znak_p = znak_s; 
    		}
    		if(znak_s == znak_p + 1) continue;
		}
	}
    
	return s_2 = " " + s + " ";
}

string skobki(string s) {
		int i, j = 0, n = 0, n_sk, m;
	double num_vir_to_sk;
	string vir_to_sk = "", a_str = "", b_str = "", s_num_vir_to_sk;

	for(i = 0; i < s.size(); i++) {
		if(s[i] == '(') {
			n++; n_sk = i;
		}
	} 

for(m = 0; m < n; m++) {
	for(i = 0; i < s.size(); i++) {
		if(i != n_sk) a_str += s[i];
		if(i == n_sk) {
			j = i + 1;
			while(s[j] != ')') {
				vir_to_sk += s[j];
				j++;
			}
			j++;
			while(j < s.size()) {
				b_str += s[j];
				j++;
			}			
			vir_to_sk = " " + vir_to_sk + " ";
			num_vir_to_sk = sl_vir(vir_to_sk);
				ostringstream ost;
                ost <<num_vir_to_sk;
                s_num_vir_to_sk = ost.str();
                
                s = a_str + s_num_vir_to_sk + b_str;
                b_str = ""; a_str = ""; vir_to_sk = "";
                break;
		}
	}
	for(i = 0; i < s.size(); i++) {
		if(s[i] == '(') {n_sk = i;}
	} 
}
return s;
}

main() 
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	SetColor(10, 0);
	cout <<  "\n***************Добро пожаловать в VIR1***************";
	cout <<"  \n=====================================================\n"
	        "Эта программа используется для вычисления значений\n"
	        "простейших выражений на четыре действия (+, -, *, /).\n\n"
	        "Строка вводится так: "
	        "(5*3-7)*4+0.5\n\nБез пробелов и запятых. "
			"Для печати десятичных дробей\nиспользуйте точки.\n\n";
	cout <<"=====================================================\n                   Успешной работы!\n=====================================================\n\n";
	cout <<"Введите строку: "; 		
	             
    string vir;
	getline(cin, vir);
	cout <<"\nРезультат: " <<sl_vir(skobki(perevod(vir)));
	
	getch();
    SetColor(15, 0);
    return 0;
}
