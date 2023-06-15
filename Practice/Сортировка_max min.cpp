//определение макс и мин элемента одномерного массива с //сортировкой
#include <iostream>
#include <math.h>
#include <stdlib.h>
using namespace std;

main() 
{
int a[10], min=a[0], p;

for(int i=0; i<=9; i++) 
{
	cout << "Input " << i + 1 << " element of array: ";
	cin >> a[i]; 
}
cout<<endl;

for(int i=0; i<=9; i++) 
{
    for(int g=i; g<=10; g++)  
    {
        if(a[i]>a[g]) {p=a[i]; a[i]=a[g]; a[g]=p;}
    }
} 
 
for(int i=0; i<=9; i++) 
{
    if(a[i]<min) min=a[i];
}

cout<<"\nmax = "<<p; 
cout<<"\nmin = "<<min;

return 0;
}
