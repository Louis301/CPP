//spiral'
#include <iostream>
using namespace std;

main()
{
	int i, j, n, s1=0, s2=0, kol, stop;
	cout <<"input N: "; cin >>n; cout <<endl;
	int a[n][n]={0};
	
	int i_n1 = 0, i_k1 = n-1, j_n1 = 0, j_k1 = n-1, n1 = n*n; 

for(kol = 0; kol <= n1; kol++) {

	for(i=i_n1; i<=i_k1; i++){
		for(j=j_n1; j<=j_k1; j++){
			if(i==i_n1) {s1++; a[i][j]=s1;} 						
		}
    }
    
    for(i=i_n1+1; i<=i_k1; i++){
		for(j=j_n1; j<=j_k1; j++){
			if(j==j_k1) {s1++; a[i][j]=s1;} 						
		}
    }
	
	for(i=i_n1; i<=i_k1; i++){
		for(j=i_k1-1; j>=i_n1; j--){
			if(i==i_k1) {s1++; a[i][j]=s1;} 					
		}
	}
	
	for(i=j_k1-1; i>=i_n1+1; i--) {
		for(j=j_n1; j<=j_k1; j++){
			if(j==j_n1) {s1++; a[i][j]=s1;} 
		}
	}
	
i_n1++; j_n1++; i_k1--; j_k1--;	 
}

	for(i=0; i<=n-1; i++){ //output table
		for(j=0; j<=n-1; j++){
			cout.width(5); cout <<a[i][j];		
		}
		cout <<'\n';
	}
cin>> stop;
}
