#include <stdio.h>

int main(void)
{
	char c;
	signed char checksum = -1;
	while((c = getchar() ) != EOF)
		{
			printf("%c", c);
			checksum += c;
		}
	printf("%d\n", checksum);

	return 0;
}
