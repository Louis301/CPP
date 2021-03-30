//сортировка с помощью вызова по ссылке
#include <stdio.h>
#include <stdlib.h>
#define size 6
void bubbleSort(int *, int);

main()
{
	int i, j, a[size];

    for(i = 0; i <= size-1; i++) {
    	a[i] = rand()%100+1;
		printf("%d\t", a[i]);
	} 
	
	bubbleSort(a, size);
	printf("\n");
	
    for(i = 0; i <= size - 1; i++) {
		printf("%d\t", a[i]);
	} 
	return 0;
}

void bubbleSort(int *array, int size1)
{
	int pass, j;
	void swap(int *, int *);
	
	for(pass = 0; pass <= size1 - 1; pass++) {
		for(j = 0; j <= size1-2; j++) {
			if(array[j] > array[j+1]) swap(&array[j], &array[j+1]);
		}
	}
}

void swap(int *element1, int *element2) 
{
	int temp;
	
	temp = *element1;
	*element1 = *element2;
	*element2 = temp;
}
