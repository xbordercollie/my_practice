#include <stdio.h>

void exchange(int *a, int *b);

int main()
{
	int x, y;
	scanf("%d %d", &x, &y);
	printf("x = %d, y = %d\n", x, y);

	exchange(&x, &y);
	printf("x = %d, y = %d\n", x, y);

	return 0;
}

void exchange(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
