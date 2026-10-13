#include <stdio.h>

struct Node {
	int Val;
	struct Node *next;
};

int main()
{
	struct Node n1,n2,n3;
	n1.Val = 10;
	n2.Val = 20;
	n3.Val = 30;

	n1.next = &n2;
	n2.next = &n3;
	n3.next = NULL;

	struct Node *p;
	p = &n1;
	int count = 0;

	while(p != NULL)
	{
		printf("%d\t", p->Val);
		count++;
		p = p->next;
	}
	printf("\ncount = %d\n", count);

	return 0;
}
