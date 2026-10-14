#include <stdio.h>
#include <stdlib.h>

struct Node {
	int Val;
	struct Node *next;
};

int main()
{
	struct Node *head = NULL;
	struct Node *tail = NULL;
	int x, count = 0;

	while(1)
	{
		scanf("%d", &x);
		if(x == 0) break;

		struct Node *new_node = malloc(sizeof(struct Node));
		new_node->Val = x;
		new_node->next = NULL;

		if(head == NULL) head = new_node;
		else tail->next = new_node;

		/*这一步留下了上一个的指针，在else中正好让next指向下一个*/
		tail = new_node;
		count++;
	}

	printf("\n\n一共存有%d个数\n", count);
	struct Node *p = head;
	while(p != NULL)
	{
		struct Node *q = p;
		printf("%d\t", p->Val);
		p = p->next;
		free(q);
	}
	printf("\n");

	return 0;
}
