//ромб
#include <iostream>
#include <Conio.h>
using namespace std;

main()
{
	int n = 5, i, j, s = 1, i_p = n/2, j_n=1, j_k=1, stop;
	int a[n][n] = {0};
	
	if(n % 2 == 0) {
		j_n = i_p; j_k = i_p - 1;
	}
	
	if(n % 2 != 0) {
		j_n = i_p+1; j_k = i_p-1;
	}
	
	for(i = 0; i <= n-1; i++) {
		if(n % 2 == 0) {
			if(i < i_p) {j_n--; j_k++;}
			if(i > i_p) {j_n++; j_k--;}
		}
		if(n % 2 != 0) {
			if(i <= i_p) {j_n--; j_k++;}
			if(i > i_p) {j_n++; j_k--;}
		}
		for(j = 0; j <= n-1; j++) {
			if(j >= j_n && j <= j_k) {a[i][j] = s; s++;}
		}
	
	}
	
	cout <<'\n';
	for(i = 0; i <= n-1; i++) {
		for(j = 0; j <= n-1; j++) {
			cout.width(5); cout <<a[i][j];
		}
		cout <<'\n';
	}

    getch();
    return 0;
}



