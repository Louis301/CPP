/*сортировка пузырьковым методом*/
#include <stdio.h>
#define size 5

main()
{
	int a[size];
	int i, pass, hold;

	printf("Data items in originale order\n");
	
	for(i=0; i<=size-1; i++) 
	printf("%4d", a[i]=rand()%20+1);
	
		for(pass=1; pass<=size-1; pass++)
			for(i=0; i<=size-2; i++)
			if (a[i]>a[i+1]) {
				hold=a[i];
				a[i]=a[i+1];
				a[i+1]=hold;
			}

 	printf("\n\nData items in ascending order\n");

	for(i=0; i<=size-1; i++) 
	printf("%4d", a[i]); 
	
	printf("\n");
	return 0;		
}

