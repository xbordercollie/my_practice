#include <stdio.h>
#include <stdlib.h>

struct Node {
        int Val;
        struct Node *next;
};

int delete_num(struct Node **head, int v);
void printf_all(struct Node *head);
void free_all(struct Node *head);
void reverse(struct Node **head);

int main()
{
        struct Node *head = NULL;
        struct Node *tail = NULL;
        int x;

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

	printf("是否翻转列表?\ty or n\n");
	char panduan;
	scanf(" %c" , &panduan);
	if(panduan == 'y')
	{
		reverse(&head);
		printf("翻转列表如下:\n");
		printf_all(head);
	}
	else if(panduan == 'n') printf("已取消翻转\n");
	else printf("输入错误\n");

        free_all(head);
        return 0;
}

void reverse(struct Node **head)
{
	struct Node *current = NULL;
	struct Node *next = *head;
	struct Node *before = NULL;

	while(next != NULL /*&& 末尾不是0*/)
	{
		before = current;			/*把上个current存入before*/
		current = next;				/*把上个current移动到上个的后一个*/
		next = current->next;			/*记录next为现在的下一站*/
		current->next = before;			/*现在的下一站记录为before*/
	}
	*head = current;				/*头指向最后的当下（改指针）*/
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
