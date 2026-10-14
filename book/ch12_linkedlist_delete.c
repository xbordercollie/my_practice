#include <stdio.h>
#include <stdlib.h>

struct Node {
	int Val;
	struct Node *next;
};

int delete_num(struct Node **head, int v);
void printf_all(struct Node *head);
void free_all(struct Node *head);

int main()
{
	struct Node *head = NULL;
        struct Node *tail = NULL;
        int x, delete_number, count = 0;

	printf("请创建链表:\n");
        while(1)
        {
                scanf("%d", &x);
                if(x == 0) break;

                struct Node *new_node = malloc(sizeof(struct Node));
                new_node->Val = x;
                new_node->next = NULL;

                if(head == NULL) head = new_node;
                else tail->next = new_node;
		tail = new_node;
	}

	printf("创建成功:\n\n");
	printf("请输入删除元素:\n");
	scanf("%d", &delete_number);

	int ret = delete_num(&head, delete_number);
	if(!ret)
	{
		printf("删除失败，不存在该元素\n");
		exit(0);
	}
	else
	{
		printf("删除成功，新列表如下:\n");
		printf_all(head);
	}

	free_all(head);
	return 0;
}

int delete_num(struct Node **head, int v)
{
	struct Node **linkp = head;                    /* 指着"装着当前节点地址的地方" */

	while (*linkp != NULL && (*linkp)->Val != v)
		linkp = &(*linkp)->next;               /* 走一格：改指"下一个地址字段" */

	if (*linkp == NULL) return 0;                  /* 走到底，没找到 */

	struct Node *old = *linkp;                     /* 存下被删节点的地址 */
	*linkp = old->next;                            /* 绕过：改"装着它地址的地方" */
	free(old);                                     /* 放掉它 */
	return 1;
}

void printf_all(struct Node *head)
{
        struct Node *p = head;
        while(p != NULL)
        {
                printf("%d\n", p->Val);
                p = p->next;
        }
}

void free_all(struct Node *head)
{
        struct Node *p = head;
        struct Node *q = p;
        while(p != NULL)
        {
                p = p->next;
                free(q);
                q = p;
        }
}

