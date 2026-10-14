#include <stdio.h>
#include <stdlib.h>

struct Node {
	int Val;
	struct Node *next;
};

int main()
{
	struct Node *p1, *p2, *p3;
	p1 = malloc(sizeof(struct Node));
	p2 = malloc(sizeof(struct Node));
	p3 = malloc(sizeof(struct Node));

	p1->Val = 10;
	p2->Val = 20;
	p3->Val = 30;

	p1->next = p2;
	p2->next = p3;
	p3->next = NULL;

	struct Node *p = p1;
	while(p != NULL)
	{
		printf("%d\n", p->Val);
		p = p->next;
	}

	free(p1);
	free(p2);
	free(p3);

	return 0;
}
