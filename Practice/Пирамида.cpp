#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;
main()
{
int n, a[n][n];
cout << "Input N: ";
cin>>n;
for(int i=0; i<=n-1; i++)
{
for(int j=0; j<=n-1; j++)
{
if(n%2!=0)
{
if(i+j==n-1 && i<n/2) {a[i][j]=i+1; cout<<a[i][j];}
if(i+j==n-1 && i>=n/2) {a[i][j]=fabs(i-n); cout<<a[i][j];}
if(i==j && i<n/2) {a[i][j]=j+1; cout<<a[i][j];}
if(i==j && i>n/2) {a[i][j]=fabs(j-n); cout<<a[i][j];}

if(i+j<n-1 && i>j) {a[i][j]=j+1;  cout<<a[i][j];}
if(i+j<n-1 && i<j) {a[i][j]=i+1; cout<<a[i][j];}
if(i+j>n-1 && i<j) {a[i][j]=fabs(j-n); cout<<a[i][j];}
if(i+j>n-1 && i>j) {a[i][j]=fabs(i-n);  cout<<a[i][j];}
}
if(n%2==0)
{
if(i+j<=n-1 && i>=j) {a[i][j]=j+1;  cout<<a[i][j];}
if(i+j<n-1 && i<j) {a[i][j]=i+1; cout<<a[i][j];}
if(i+j>=n-1 && i<=j) {a[i][j]=fabs(j-n); cout<<a[i][j];}
if(i+j>n-1 && i>j) {a[i][j]=fabs(i-n);  cout<<a[i][j];}
}
}
cout<<endl;
}
}
