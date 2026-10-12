#include <stdio.h>

void print_arr(int *arr, int n);

int main()
{
	int arr[] = {1,3,5,7,9};
	print_arr(arr, 5);

	return 0;
}

void print_arr(int *arr, int n)
{
	int *p = arr;
	for(p=arr; p<arr+n; p++)
	{
		printf("%d\t", *p);
	}
	printf("\n");
}
