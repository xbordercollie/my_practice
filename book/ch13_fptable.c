#include <stdio.h>
#include <stdlib.h>

int (*fp)(int, int);
int caculate_plus(int a, int b);
int caculate_minus(int a, int b);

int main()
{
	int (*caculate_func[])(int ,int) = {
		caculate_plus, caculate_minus };

	int x;
	int a = 2, b = 3;
	scanf("%d", &x);

	printf("%d\n", caculate_func[x](a, b));

	return 0;
}

int caculate_plus(int a, int b)
{
	return a + b;
}

int caculate_minus(int a, int b)
{
	return a - b;
}
