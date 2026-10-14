#include <stdio.h>
#include <stdlib.h>

struct Node {
        int Val;
        struct Node *next;
};

struct Node* insert_head(struct Node *head, int v);
void free_all(struct Node *head);
void printf_all(struct Node *head);

int main()
{
        int x, v;
        struct Node *head = NULL;
        struct Node *tail = NULL;
        struct Node *new_head = NULL;

        printf("请创建链表\n");

        while(1)
        {
                scanf("%d", &x);
                if(x == 0) break;

                struct Node *new_node = malloc(sizeof(struct Node));
                new_node->Val = x;
                new_node->next = NULL;

                if(head ==NULL) head = new_node;
                else tail->next = new_node;

                tail = new_node;
        }

        printf("\n\n链表创建完毕：\n");
	printf_all(head);

        printf("\n\n请输入新增表头：\n");
        scanf("%d", &v);

	struct Node *panduan = insert_head(head, v);
        if(panduan == NULL) exit(0);
	else new_head = panduan;

        printf("\n\n新链表创建完毕\n");
	printf_all(new_head);

	free_all(new_head);
        return 0;
}

struct Node* insert_head(struct Node *head, int v)
{
        struct Node *new_head = malloc(sizeof(struct Node));
        if(new_head == NULL)
        {
                printf("添加失败!\n");
                return NULL;
        }
        else
        {
                new_head->next = head;
                new_head->Val = v;
        }

        return new_head;
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
