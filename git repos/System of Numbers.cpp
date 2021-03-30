/*
	Name: System of numbers
	Copyright: -
	Author: Louis
	Date: 10.09.19 22:46
	Description: -
*/

#include <iostream>
#include <math.h>
#include <Windows.h>
#include <sstream>
#include <string>
#include <conio.h>
using namespace std;

int alfabeth (char s_n) {
	int n2;
	if (s_n == '0') n2 = 0;
	if (s_n == '1') n2 = 1;
	if (s_n == '2') n2 = 2;
	if (s_n == '3') n2 = 3;
	if (s_n == '4') n2 = 4;
	if (s_n == '5') n2 = 5;
	if (s_n == '6') n2 = 6;
	if (s_n == '7') n2 = 7;
	if (s_n == '8') n2 = 8;
	if (s_n == '9') n2 = 9;
	
    if (s_n == 'a') n2 = 10;
    if (s_n == 'b') n2 = 11;
    if (s_n == 'c') n2 = 12;
    if (s_n == 'd') n2 = 13;
    if (s_n == 'e') n2 = 14;
    if (s_n == 'f') n2 = 15;
 
    return n2;
}

char alfabeth2 (int n) {
	char s_n2;
	if (n == 0) s_n2 = '0';
	if (n == 1) s_n2 = '1';
	if (n == 2) s_n2 = '2';
	if (n == 3) s_n2 = '3';
	if (n == 4) s_n2 = '4';
	if (n == 5) s_n2 = '5';
	if (n == 6) s_n2 = '6';
	if (n == 7) s_n2 = '7';
	if (n == 8) s_n2 = '8';
	if (n == 9) s_n2 = '9';
	
    if (n == 10) s_n2 = 'a';
    if (n == 11) s_n2 = 'b';
    if (n == 12) s_n2 = 'c';
    if (n == 13) s_n2 = 'd';
    if (n == 14) s_n2 = 'e';
    if (n == 15) s_n2 = 'f';
    
    return s_n2;
}
 
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	long int num, i=0, k=0, ss_res, ss_num, res[100], kol = 0, summ = 0, num2[100];	
	ostringstream ost; 
	string s_num; string s_num2; string res2;
	char s_num3;
	
	cout <<"Эта программа переводит число с основанием X\n           в число с основанием Y\n\n";
	cout <<"Введите исходное число: "; getline (cin, s_num);
	cout <<"Введите основание исходного числа (X): "; cin>> ss_num;
    cout <<"Введите основание результата (Y): "; cin>> ss_res;
    cout <<"\n---------------------------\n";

//***************************************перевод в 10-ную СС   
    if (ss_res == 10) {
        
    if (ss_num < 16) { //из строки в целочисленный массив
        for (i = 0; i <= s_num.size()-1; i++) { 
    	s_num2 = s_num[i]; 
    	num2[i] = atoi (s_num2.c_str());
    	kol++;
   	    } 
   	}
   	
   	if (ss_num >= 16) { //из 16-ной СС в целочисленный массив 
   		for (i = 0; i <= s_num.size()-1; i++) { 
    	s_num3 = s_num[i];
    	num2[i] = alfabeth (s_num3);
    	kol++;
    }
	}
   	    
		kol-=1;
	
	    for (i = 0; i <= s_num.size()-1; i++) {
	    	
			cout <<num2[i] <<"*" <<ss_num <<"^"<<kol; //вывод операций над числами 
	    	if (kol != 0) cout <<" + "; else {cout <<" = "<< summ+num2[i]; summ+=num2[i]; break;}
	    	
			num2[i] = num2[i]*pow(ss_num, kol);
	    	kol--;
	    	summ+=num2[i];
		}
		cout <<"\n---------------------------\n\n" <<"Результат: "<<summ ;
	}
//***************************************перевод из 10-ной СС   
if (ss_num == 10) {
	num = atoi (s_num.c_str());
		
	if (ss_res <= 10) {
	    do {		
		    cout <<num<<" / "<<ss_res<<" = "<<num / ss_res<<"; остаток "<<num % ss_res<<"\n"; //вывод операций над числами 
			res[i] = num % ss_res;
		    num /= ss_res;
		    i++;
		    k++;
	    } while (num != 0);
	    cout <<"---------------------------\n\n" <<"Результат: ";
	    for (i = k-1; i >= 0; i--) {
		    cout <<res[i];
	    }
	}
	
	if (ss_res > 10) {
		do {		
		    cout <<num<<" / "<<ss_res<<" = "<<num / ss_res<<"; остаток "<<num % ss_res;  //вывод операций над числами 
		    if (num % ss_res > 9) cout <<" = " <<alfabeth2 (num % ss_res)<< "\n";
		    if (num % ss_res <= 9) cout <<"\n";
			res2[i] = alfabeth2 (num % ss_res);
		    num /= ss_res;
		    i++;
		    k++;
	    } while (num != 0);
		cout <<"---------------------------\n\n" <<"Результат: ";
	    for (i = k-1; i >= 0; i--) {
		    cout <<res2[i];
	    }
    }
	    
	    k=0; i=0; 
    }  
//***************************************остальные переводы
if (ss_num != 10 && ss_res != 10) {
	
   if (ss_num < 16) { //из строки в целочисленный массив
        for (i = 0; i <= s_num.size()-1; i++) { 
    	s_num2 = s_num[i]; 
    	num2[i] = atoi (s_num2.c_str());
    	kol++;
   	    } 
   	}
   	
   	if (ss_num >= 16) { //из 16-ной СС в целочисленный массив 
   		for (i = 0; i <= s_num.size()-1; i++) { 
    	s_num3 = s_num[i];
    	num2[i] = alfabeth (s_num3);
    	kol++;
    }
	}
   	    
	kol-=1;
	
	    for (i = 0; i <= s_num.size()-1; i++) {
	    	
			cout <<num2[i] <<"*" <<ss_num <<"^"<<kol; //вывод операций над числами 
	    	if (kol != 0) cout <<" + "; else {cout <<" = "<< summ+num2[i]; summ+=num2[i]; break;}
	    	
			num2[i] = num2[i]*pow(ss_num, kol);
	    	kol--;
	    	summ+=num2[i];
		}
		cout <<"\n\n"; i=0;	
		 
	if (ss_res < 10) {
	    do {		
		    cout <<summ<<" / "<<ss_res<<" = "<<summ / ss_res<<"; остаток "<<summ % ss_res<<"\n"; //вывод операций над числами 
			res[i] = summ % ss_res;
		    summ /= ss_res;
		    i++;
		    k++;
	    } while (summ != 0);
	    cout <<"---------------------------\n\n" <<"Результат: ";
	    for (i = k-1; i >= 0; i--) {
		    cout <<res[i];
	    }
	}
	
	if (ss_res > 10) {
		do {		
		    cout <<summ<<" / "<<ss_res<<" = "<<summ / ss_res<<"; остаток "<<summ % ss_res;  //вывод операций над числами 
		    if (summ % ss_res > 9) cout <<" = " <<alfabeth2 (summ % ss_res)<< "\n";
		    if (summ % ss_res <= 9) cout <<"\n";
			res2[i] = alfabeth2 (summ % ss_res);
		    summ /= ss_res;
		    i++;
		    k++;
	    } while (summ != 0);
		cout <<"---------------------------\n\n" <<"Результат: ";

	    for (i = k-1; i >= 0; i--) {
		    cout <<res2[i];
	    }
    }
	    k=0; i=0; 
}

	cout <<"\n===========================\n";
	getch();
    return 0;
}
